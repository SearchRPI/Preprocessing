import sys
import os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))

import pytest
import json
from unittest.mock import patch, MagicMock
from crawler.crawler import (
    extract_links,
    is_same_domain,
    send_to_transformer,
    fetch_dynamic_page,
)

# -----------------------
# Test extract_links()
# -----------------------

def test_extract_links_resolves_relative():
    html = """
        <html>
            <body>
                <a href="/page1">Page 1</a>
                <a href="https://example.com/page2">Page 2</a>
            </body>
        </html>
    """
    links = extract_links(html, "https://example.com")
    assert "https://example.com/page1" in links
    assert "https://example.com/page2" in links
    assert len(links) == 2

# -----------------------
# Test is_same_domain()
# -----------------------

def test_is_same_domain_valid():
    assert is_same_domain("https://projecteuler.net/about", "projecteuler.net")

def test_is_same_domain_subdomain():
    assert is_same_domain("https://sub.projecteuler.net/page", "projecteuler.net")

def test_is_same_domain_invalid():
    assert not is_same_domain("https://example.com/page", "projecteuler.net")

# -----------------------
# Test send_to_transformer()
# -----------------------

@patch("socket.create_connection")
def test_send_to_transformer(mock_create_conn):
    mock_sock = MagicMock()
    mock_create_conn.return_value.__enter__.return_value = mock_sock

    test_url = "https://example.com"
    test_html = "<html><p>Hello</p></html>"

    send_to_transformer(test_url, test_html)

    sent_data = mock_sock.sendall.call_args[0][0].decode()
    payload = json.loads(sent_data.strip())

    assert payload["url"] == test_url
    assert "Hello" in payload["html"]

# -----------------------
# Test fetch_dynamic_page()
# -----------------------
@patch("crawler.crawler.WebDriverWait")
def test_fetch_dynamic_page_success(mock_wait):
    mock_driver = MagicMock()
    mock_driver.page_source = "<html><body>Page</body></html>"

    mock_wait.return_value.until.return_value = True

    html = fetch_dynamic_page("https://example.com", mock_driver)
    assert "Page" in html
