#include "../parser.h"

int verifySection(char* tagName) {
    // Tag name must be null or importants
    char sectionTag[] = "section";
    return compareStr(tagName, sectionTag);
}

a_tag  parseSection(reader cursor) {
    t_parser p_contenu = createContenuParser();

    a_tag  section = createTag(e_section);

    a_tag  child = p_contenu.execute(cursor); 

    if(child == TAG_NULL){
        fprintf(stderr, "expected contenu in section\n");
        exit(1);
    }

    readClosingTag(cursor);
    assertCurrentTag(cursor, "section");

    addChild(section, child);

    return section;
}

t_parser createSectionParser() {
    t_parser parser;
    parser.execute = parseSection;
    parser.verify = verifySection;

    return parser;
}