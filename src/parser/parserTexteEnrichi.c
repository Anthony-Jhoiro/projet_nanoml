#include "parser.h"

int verifyTexteEnrichi(char* tagName) {
    return 1;
}

a_tag  parseTexteEnrichi(reader cursor) {
    // Read document
    t_parser p_document = createDocumentParser();

    readOpeningTag(cursor);
    if (!p_document.verify(cursor->currentTag)) {
        fprintf(stderr, "Error: Document tag is needed");
        exit(5);
    }

    a_tag  document = p_document.execute(cursor);

    // Read Annexes
    t_parser p_annexes = createAnnexesParser();

    a_tag  annexes = p_annexes.execute(cursor);

    // Creation du tag
    a_tag  texteEnrichi = createTag(e_texte_enrichi);
    addChild(texteEnrichi, document);

    if (annexes != TAG_NULL) {
        addChild(texteEnrichi, annexes);
    }

    return texteEnrichi;
}

t_parser createTexteEnrichiParser() {
    t_parser parser;
    parser.execute = parseTexteEnrichi;
    parser.verify = verifyTexteEnrichi;

    return parser;
}