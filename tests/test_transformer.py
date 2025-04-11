import sys
import os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))

import json
import socket
from unittest.mock import patch, MagicMock
from text_transformation.text_transformer import (
    extract_tagged_words,
    forward_to_indexer,
    handle_client,
)

# -----------------------
# Test extract_tagged_words()
# -----------------------

def test_extract_tagged_words_simple():
    html = """
    <html>
      <head><title>My Page</title></head>
      <body>
        <h1>Header Title</h1>
        <p>This is a test. Test this again!</p>
        <span>Header title</span>
      </body>
    </html>
    """
    result = extract_tagged_words(html)

    assert result["header"]["count"] == 2
    assert result["title"]["tag"] == "title"  # highest priority
    assert result["test"]["count"] == 2
    assert result["again"]["tag"] == "p"

# -----------------------
# Test forward_to_indexer()
# -----------------------

@patch("socket.create_connection")
def test_forward_to_indexer(mock_conn):
    mock_sock = MagicMock()
    mock_conn.return_value.__enter__.return_value = mock_sock

    sample_msg = {
        "url": "https://example.com",
        "words": {
            "test": {"count": 1, "tag": "h1"}
        }
    }

    forward_to_indexer(sample_msg)

    sent_data = mock_sock.sendall.call_args[0][0].decode()
    payload = json.loads(sent_data.strip())

    assert payload["url"] == "https://example.com"
    assert "test" in payload["words"]

# -----------------------
# Test handle_client() with socket mock
# -----------------------

@patch("transformer.forward_to_indexer")
def test_handle_client(mock_forward):
    fake_conn = MagicMock()
    html = "<h1>Test Page</h1><p>Paragraph test test</p>"
    payload = {
        "url": "https://test.com",
        "html": html
    }

    # Simulate socket recv() in chunks
    fake_conn.recv.side_effect = [
        (json.dumps(payload) + "\n").encode(),  # first chunk
        b''  # signals connection closed
    ]

    handle_client(fake_conn, ("127.0.0.1", 12345))

    args = mock_forward.call_args[0][0]
    assert args["url"] == "https://test.com"
    assert args["words"]["test"]["count"] == 3
    assert args["words"]["test"]["tag"] in {"h1", "p"}
