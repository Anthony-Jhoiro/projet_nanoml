#include "../parser.h"

int verifyAnnexeUnitaire(char* tagName) {
    char annexeTag[] = "annexe";
    return compareStr(tagName, annexeTag);
}

a_tag  parseAnnexeUnitaire(reader cursor) {
    t_parser p_contenu = createContenuParser();

    a_tag  child = p_contenu.execute(cursor);   

    // Verify closing tag
    readClosingTag(cursor);
    assertCurrentTag(cursor, "annexe");

    // Creation du tag
    a_tag  annexe = createTag(e_annexe);
    addChild(annexe, child);

    return annexe;
}

t_parser createAnnexeUnitaireParser() {
    t_parser parser;
    parser.execute = parseAnnexeUnitaire;
    parser.verify = verifyAnnexeUnitaire;

    return parser;
}