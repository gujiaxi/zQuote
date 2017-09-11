#define TEXT_WIDTH     4000
#define BASE_FONT_SIZE  200
#define MARGIN_X        240
#define MARGIN_Y        280
#define GAP_SIZE        230
#define TITLE_RESIZE    0.6
#define AUTHOR_RESIZE   0.5

struct text_content {
    char * body;
    char * title;
    char * author;
};

void make_quote_img(char * body, char * title, char * author);
