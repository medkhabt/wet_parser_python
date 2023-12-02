/***************************************************************************/
/*    This code is part of WWW grabber called pavuk                        */
/*    Copyright (c) 1997 - 2001 Stefan Ondrejicka                          */
/*    Distributed under GPL 2 or later                                     */
/***************************************************************************/

#include "config.h"

#include "html.h"
#include "tools.h"

/*************************************************************/
/* tabulka znamych znaciek a atributov ktore sa spracovavaju */
/* FIXME: Translate me!                                      */
/*************************************************************/
html_tag_t html_link_tags[] = {
  {HTML_TAG_HEAD, "HEAD",
      {
          {HTML_ATTRIB_PROFILE, "PROFILE", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_BODY, "BODY",
      {
          {HTML_ATTRIB_BACKGROUND, "BACKGROUND", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_JSEVENT, "ONLOAD", LINK_JS | LINK_DOWNLD | LINK_INLINE}
          ,
          {HTML_ATTRIB_JSEVENT, "ONUNLOAD",
            LINK_JS | LINK_DOWNLD | LINK_INLINE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_TABLE, "TABLE",
      {
          {HTML_ATTRIB_BACKGROUND, "BACKGROUND", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_TH, "TH",
      {
          {HTML_ATTRIB_BACKGROUND, "BACKGROUND", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_TD, "TD",
      {
          {HTML_ATTRIB_BACKGROUND, "BACKGROUND", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_IMG, "IMG",
      {
          {HTML_ATTRIB_SRC, "SRC", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_LOWSRC, "LOWSRC", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_LONGDESC, "LONGDESC", LINK_DOWNLD}
          ,
          {HTML_ATTRIB_USEMAP, "USEMAP", LINK_DOWNLD | LINK_INLINE}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_JSEVENT, "ONMOUSEOVER",
            LINK_JS | LINK_DOWNLD | LINK_INLINE}
          ,
          {HTML_ATTRIB_JSEVENT, "ONCLICK", LINK_JS | LINK_DOWNLD | LINK_INLINE}
          ,
          {HTML_ATTRIB_JSEVENT, "ONDBLCLICK",
            LINK_JS | LINK_DOWNLD | LINK_INLINE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_INPUT, "INPUT",
      {
          {HTML_ATTRIB_SRC, "SRC", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_USEMAP, "USEMAP", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_FRAME, "FRAME",
      {
          {HTML_ATTRIB_SRC, "SRC", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_LONGDESC, "LONGDESC", LINK_DOWNLD}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_IFRAME, "IFRAME",
      {
          {HTML_ATTRIB_SRC, "SRC", LINK_DOWNLD}
          ,
          {HTML_ATTRIB_LONGDESC, "LONGDESC", LINK_DOWNLD}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_APPLET, "APPLET",
      {
          {HTML_ATTRIB_CODEBASE, "CODEBASE", 0}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_SCRIPT, "SCRIPT",
      {
          {HTML_ATTRIB_SRC, "SRC", LINK_INLINE | LINK_SCRIPT | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_SOUND, "SOUND",
      {
          {HTML_ATTRIB_SRC, "SRC", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_BGSOUND, "BGSOUND",
      {
          {HTML_ATTRIB_SRC, "SRC", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_EMBED, "EMBED",
      {
          {HTML_ATTRIB_SRC, "SRC", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_AREA, "AREA",
      {
          {HTML_ATTRIB_HREF, "HREF", LINK_DOWNLD}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_JSEVENT, "ONCLICK", LINK_JS | LINK_DOWNLD | LINK_INLINE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_BASE, "BASE",
      {
          {HTML_ATTRIB_HREF, "HREF", 0}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_FIG, "FIG",
      {
          {HTML_ATTRIB_SRC, "SRC", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_OVERLAY, "OVERLAY",
      {
          {HTML_ATTRIB_SRC, "SRC", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_A, "A",
      {
          {HTML_ATTRIB_HREF, "HREF", LINK_DOWNLD}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_JSEVENT, "ONMOUSEOVER",
            LINK_JS | LINK_DOWNLD | LINK_INLINE}
          ,
          {HTML_ATTRIB_JSEVENT, "ONCLICK", LINK_JS | LINK_DOWNLD | LINK_INLINE}
          ,
          {HTML_ATTRIB_JSEVENT, "ONDBLCLICK",
            LINK_JS | LINK_DOWNLD | LINK_INLINE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_LINK, "LINK",
      {
          {HTML_ATTRIB_HREF, "HREF", LINK_DOWNLD | LINK_INLINE}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_FORM, "FORM",
      {
          {HTML_ATTRIB_ACTION, "ACTION", /* LINK_DOWNLD | */ LINK_FORM}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_META, "META",
      {
          {HTML_ATTRIB_CONTENT, "CONTENT", LINK_DOWNLD}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_INS, "INS",
      {
          {HTML_ATTRIB_CITE, "CITE", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_DEL, "DEL",
      {
          {HTML_ATTRIB_CITE, "CITE", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_Q, "Q",
      {
          {HTML_ATTRIB_CITE, "CITE", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_SPAN, "SPAN",
      {
          {HTML_ATTRIB_HREF, "HREF", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_DIV, "DIV",
      {
          {HTML_ATTRIB_HREF, "HREF", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_OBJECT, "OBJECT",
      {
          {HTML_ATTRIB_DATA, "DATA", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_USEMAP, "USEMAP", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_JSEVENT, "ONMOUSEOVER",
            LINK_JS | LINK_DOWNLD | LINK_INLINE}
          ,
          {HTML_ATTRIB_JSEVENT, "ONCLICK", LINK_JS | LINK_DOWNLD | LINK_INLINE}
          ,
          {HTML_ATTRIB_JSEVENT, "ONDBLCLICK",
            LINK_JS | LINK_DOWNLD | LINK_INLINE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_LAYER, "LAYER",
      {
          {HTML_ATTRIB_SRC, "SRC", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_ADDRESS, "ADDRESS",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_BLOCKQUOTE, "BLOCKQUTE",
      {
          {HTML_ATTRIB_CITE, "CITE", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_CENTER, "CENTER",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_H1, "H1",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_H2, "H2",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_H3, "H3",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_H4, "H4",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_H5, "H5",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_H6, "H6",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_HR, "HR",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_ISINDEX, "ISINDEX",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_P, "P",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_PRE, "PRE",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_NOSCRIPT, "NOSCRIPT",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_DIR, "DIR",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_DL, "DL",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_DT, "DT",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_DD, "DD",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_LI, "LI",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_MENU, "MENU",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_OL, "OL",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_UL, "UL",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_CAPTION, "CAPTION",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_COLGROUP, "COLGROUP",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_COL, "COL",
      {
          {HTML_ATTRIB_BACKGROUND, "BACKGROUND", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_THEAD, "THEAD",
      {
          {HTML_ATTRIB_BACKGROUND, "BACKGROUND", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_TFOOT, "TFOOT",
      {
          {HTML_ATTRIB_BACKGROUND, "BACKGROUND", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_TBODY, "TBODY",
      {
          {HTML_ATTRIB_BACKGROUND, "BACKGROUND", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_FIELDSET, "FIELDSET",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_BUTTON, "BUTTON",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_LEGEND, "LEGEND",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_LABEL, "LABEL",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_SELECT, "SELECT",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_OPTGROUP, "OPTGROUP",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_OPTION, "OPTION",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_TEXTAREA, "TEXTAREA",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_BDO, "BDO",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_BR, "BR",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_FONT, "FONT",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_MAP, "MAP",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_SUB, "SUB",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_SUP, "SUP",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_ABBR, "ABBR",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_ACRONYM, "ACRONYM",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_CITE, "CITE",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_CODE, "CODE",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_DFN, "DFN",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_EM, "EM",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_KBD, "KBD",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_SAMP, "SAMP",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_STRONG, "STRONG",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_VAR, "VAR",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_B, "B",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_BIG, "BIG",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_I, "I",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_S, "S",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_SMALL, "SMALL",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_STRIKE, "STRIKE",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_TT, "TT",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_U, "U",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_FRAMESET, "FRAMESET",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_JSEVENT, "ONLOAD", LINK_JS | LINK_DOWNLD | LINK_INLINE}
          ,
          {HTML_ATTRIB_JSEVENT, "ONUNLOAD",
            LINK_JS | LINK_DOWNLD | LINK_INLINE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_NOFRAMES, "NOFRAMES",
      {
          {HTML_ATTRIB_STYLE, "STYLE", LINK_STYLE}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
  ,
  {HTML_TAG_CSOBJ, "CSOBJ",
      {
          {HTML_ATTRIB_HT, "HT", LINK_INLINE | LINK_DOWNLD}
          ,
          {HTML_ATTRIB_NULL, NULL, 0}
        }
    }
};

int html_link_tags_num(void)
{
  return NUM_ELEM(html_link_tags);
}
