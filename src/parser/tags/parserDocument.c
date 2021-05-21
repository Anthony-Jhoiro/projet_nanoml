#include "../parser.h"

int verifyDocument(char* tagName) {
    char documentTag[] = "document";
    return compareStr(tagName, documentTag);
}

a_tag  parseDocument(reader cursor) {
    t_parser p_contenu = createContenuParser();

    // readOpeningTag(cursor);
    // if (!p_contenu.verify(cursor->currentTag)) {
    //     fprintf(stderr, "Error: Empty document.");
    //     exit(4);
    // }

    a_tag  child = p_contenu.execute(cursor);   

    // Verify closing tag
    readClosingTag(cursor);
    assertCurrentTag(cursor, "document");

    // Creation du tag
    a_tag  document = createTag(e_document);
    addChild(document, child);

    return document;
}

t_parser createDocumentParser() {
    t_parser parser;
    parser.execute = parseDocument;
    parser.verify = verifyDocument;

    return parser;
}