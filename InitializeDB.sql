CREATE TABLE IF NOT EXISTS users (
        username VARCHAR(255) PRIMARY KEY,
        password_md5 VARCHAR(32) NOT NULL,
        fullname VARCHAR(255) NOT NULL
) WITHOUT ROWID;


CREATE TABLE IF NOT EXISTS items (
        name VARCHAR(255) NOT NULL
);


CREATE TABLE IF NOT EXISTS providers (
        name VARCHAR(255)
);


CREATE TABLE IF NOT EXISTS docs (
        status CHAR(1) CHECK(status IN ("N", "A")),
        doc_type VARCHAR(50) CHECK (doc_type IN ("INCOME", "CASH_VOUCHER")),
        date_create DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
        date_apply DATETIME DEFAULT NULL
);


CREATE TABLE IF NOT EXISTS income_docs (
        doc_id INT NOT NULL PRIMARY KEY REFERENCES docs(rowid),
        provider_id INT NOT NULL REFERENCES providers(rowid)
) WITHOUT ROWID;


CREATE TABLE IF NOT EXISTS doc_items (
        doc_id INT NOT NULL REFERENCES docs(rowid),
        item_id INT NOT NULL REFERENCES items(rowid),
        item_count INT NOT NULL,
        price REAL NOT NULL,
        PRIMARY KEY (doc_id, item_id)
) WITHOUT ROWID;


CREATE TABLE IF NOT EXISTS item_barcodes (
        item_id INT NOT NULL REFERENCES items(rowid),
        barcode VARCHAR(30) NOT NULL,
        PRIMARY KEY (item_id, barcode)
) WITHOUT ROWID;


CREATE TABLE IF NOT EXISTS item_price (
        item_id INT NOT NULL REFERENCES items(rowid),
        date_start DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
        price REAL NOT NULL DEFAULT 0.0,
        PRIMARY KEY (item_id, date_start)
) WITHOUT ROWID;


CREATE TABLE IF NOT EXISTS warehouse_items (
        item_id INT NOT NULL REFERENCES items(rowid) PRIMARY KEY,
        item_count INT NOT NULL,
        price REAL NOT NULL DEFAULT 0.0
) WITHOUT ROWID;