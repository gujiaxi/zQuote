#include <stdio.h>
#include <stdlib.h>
#include <pango/pangocairo.h>

#include "qcard.h"

void layout_stylize(PangoLayout *layout, char *text,
                    char *font_family, double font_resize, int font_italic,
                    int *layout_width, int *layout_height)
{
    // text
    pango_layout_set_text(layout, text, -1);
    pango_layout_set_wrap(layout, PANGO_WRAP_WORD);
    pango_layout_set_width(layout, TEXT_WIDTH * PANGO_SCALE);
    // font
    PangoFontDescription *font;
    font = pango_font_description_new();
    pango_font_description_set_family(font, font_family);
    pango_font_description_set_weight(font, PANGO_WEIGHT_NORMAL);
    if (font_italic) pango_font_description_set_style(font, PANGO_STYLE_ITALIC);
    pango_font_description_set_size(font, font_resize * BASE_FONT_SIZE*PANGO_SCALE);
    pango_layout_set_font_description(layout, font);
    pango_font_description_free(font);
    pango_layout_get_size(layout, layout_width, layout_height);
}

int draw_text(cairo_t *cr, struct text_content ct, int *region_width, int *region_height)
{
    PangoLayout *layout;
    int body_width[1] = {0};
    int body_height[1] = {0};
    int title_width[1] = {0};
    int title_height[1] = {0};
    int author_width[1] = {0};
    int author_height[1] = {0};

    cairo_translate(cr, 0, 0);
    layout = pango_cairo_create_layout(cr);

    // --- body
    layout_stylize(layout, ct.body, "Serif", 1.0, 0, body_width, body_height);
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    pango_cairo_show_layout(cr, layout);
    // --- title
    if (ct.title) {
        cairo_move_to(cr, 0, *body_height / PANGO_SCALE + GAP_SIZE);
        layout_stylize(layout, ct.title, "Sans", TITLE_RESIZE, 1, title_width, title_height);
        cairo_set_source_rgb(cr, 0.3, 0.3, 0.3);
        pango_cairo_show_layout(cr, layout);
        *title_height += GAP_SIZE * PANGO_SCALE;
        // --- author
        if (ct.author) {
            cairo_move_to(cr, 0, *body_height / PANGO_SCALE + *title_height / PANGO_SCALE);
            layout_stylize(layout, ct.author, "Sans", AUTHOR_RESIZE, 0, author_width, author_height);
            cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
            pango_cairo_show_layout(cr, layout);
        }
    }

    *region_width = *body_width;
    *region_height = *body_height + *title_height + *author_height;

    g_object_unref(layout);

    return 0;
}

void make_quote_img(char * body, char * title, char * author) {
    cairo_t *cr;
    cairo_surface_t *virtual_surface;
    cairo_surface_t *image_surface;

    virtual_surface = cairo_recording_surface_create(CAIRO_CONTENT_COLOR_ALPHA, NULL);
    cr = cairo_create(virtual_surface);
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_paint(cr);

    // draw text
    int region_width[1] = {0};
    int region_height[1] = {0};
    struct text_content tc = {body, title, author};
    draw_text(cr, tc, region_width, region_height);

    // write to png file
    image_surface = cairo_surface_create_for_rectangle(virtual_surface, -MARGIN_X, -MARGIN_Y,
                                                       *region_width / PANGO_SCALE + 2*MARGIN_X,
                                                       *region_height / PANGO_SCALE + 2*MARGIN_Y);
    cairo_surface_write_to_png(image_surface, "output.png");
    
    // clean envs
    cairo_destroy(cr);
    cairo_surface_destroy(virtual_surface);
    cairo_surface_destroy(image_surface);
}
