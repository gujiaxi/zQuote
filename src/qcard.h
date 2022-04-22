#define TEXT_WIDTH     2000
#define BASE_FONT_SIZE  100
#define MARGIN_X        120
#define MARGIN_Y        140
#define GAP_SIZE        125
#define TITLE_RESIZE    0.7
#define AUTHOR_RESIZE   0.6

struct text_content {
    char * body;
    char * title;
    char * author;
};

void make_quote_img(char * body, char * title, char * author);
