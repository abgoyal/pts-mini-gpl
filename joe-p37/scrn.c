/*
 *	Device independant TTY interface for JOE
 *	Copyright
 *		(C) 1992 Joseph H. Allen
 *
 *	This file is part of JOE (Joe's Own Editor)
 */
#include "types.h"

int bg_text = 0; /* Background color for text */
int skiptop = 0;
int env_lines = 0;
int env_columns = 0;
int notite = 0;
int usetabs = 0;
int assume_color = 0;
int assume_256color = 0;

/* How to display characters (especially the control ones) */
/* here are characters ... */
unsigned char xlatc[256] = {
	 64,  65,  66,  67,  68,  69,  70,  71,			/*   8 */
	 72,  73,  74,  75,  76,  77,  78,  79,			/*  16 */
	 80,  81,  82,  83,  84,  85,  86,  87,			/*  24 */
	 88,  89,  90,  91,  92,  93,  94,  95,			/*  32 */
	 32,  33,  34,  35,  36,  37,  38,  39,			/*  40 */
	 40,  41,  42,  43,  44,  45,  46,  47,			/*  48 */
	 48,  49,  50,  51,  52,  53,  54,  55,			/*  56 */
	 56,  57,  58,  59,  60,  61,  62,  63,			/*  64 */

	 64,  65,  66,  67,  68,  69,  70,  71,			/*  72 */
	 72,  73,  74,  75,  76,  77,  78,  79,			/*  80 */
	 80,  81,  82,  83,  84,  85,  86,  87,			/*  88 */
	 88,  89,  90,  91,  92,  93,  94,  95,			/*  96 */
	 96,  97,  98,  99, 100, 101, 102, 103,			/* 104 */
	104, 105, 106, 107, 108, 109, 110, 111,			/* 112 */
	112, 113, 114, 115, 116, 117, 118, 119,			/* 120 */
	120, 121, 122, 123, 124, 125, 126,  63,			/* 128 */

	 64,  65,  66,  67,  68,  69,  70,  71,			/* 136 */
	 72,  73,  74,  75,  76,  77,  78,  79,			/* 144 */
	 80,  81,  82,  83,  84,  85,  86,  87,			/* 152 */
	 88,  89,  90,  91,  92,  93,  94,  95,			/* 160 */
	 32,  33,  34,  35,  36,  37,  38,  39,			/* 168 */
	 40,  41,  42,  43,  44,  45,  46,  47,			/* 176 */
	 48,  49,  50,  51,  52,  53,  54,  55,			/* 184 */
	 56,  57,  58,  59,  60,  61,  62,  63,			/* 192 */

	 64,  65,  66,  67,  68,  69,  70,  71,			/* 200 */
	 72,  73,  74,  75,  76,  77,  78,  79,			/* 208 */
	 80,  81,  82,  83,  84,  85,  86,  87,			/* 216 */
	 88,  89,  90,  91,  92,  93,  94,  95,			/* 224 */
	 96,  97,  98,  99, 100, 101, 102, 103,			/* 232 */
	104, 105, 106, 107, 108, 109, 110, 111,			/* 240 */
	112, 113, 114, 115, 116, 117, 118, 119,			/* 248 */
	120, 121, 122, 123, 124, 125, 126,  63			/* 256 */
};
/* ... and here their attributes */ 
unsigned xlata[256] = {
	UNDERLINE, UNDERLINE, UNDERLINE, UNDERLINE,		/*   4 */
	UNDERLINE, UNDERLINE, UNDERLINE, UNDERLINE,		/*   8 */
	UNDERLINE, UNDERLINE, UNDERLINE, UNDERLINE,		/*  12 */
	UNDERLINE, UNDERLINE, UNDERLINE, UNDERLINE,		/*  16 */
	UNDERLINE, UNDERLINE, UNDERLINE, UNDERLINE,		/*  20 */
	UNDERLINE, UNDERLINE, UNDERLINE, UNDERLINE,		/*  24 */
	UNDERLINE, UNDERLINE, UNDERLINE, UNDERLINE,		/*  28 */
	UNDERLINE, UNDERLINE, UNDERLINE, UNDERLINE,		/*  32 */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,		/*  48 */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,		/*  64 */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,		/*  80 */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,		/*  96 */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,		/* 112 */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, UNDERLINE,	/* 128 */

	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 130 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 132 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 134 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 136 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 138 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 140 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 142 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 144 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 146 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 148 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 150 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 152 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 154 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 156 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 158 */
	INVERSE + UNDERLINE, INVERSE + UNDERLINE,		/* 160 */

	INVERSE, INVERSE, INVERSE, INVERSE,			/* 164 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 168 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 172 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 176 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 180 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 184 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 188 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 192 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 196 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 200 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 204 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 208 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 212 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 216 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 220 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 224 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 228 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 232 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 236 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 240 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 244 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 248 */
	INVERSE, INVERSE, INVERSE, INVERSE,			/* 252 */
	INVERSE, INVERSE, INVERSE, INVERSE + UNDERLINE		/* 256 */
};

/* Set attributes */

int set_attr(SCRN *t, int c)
{
	int e;

	c &= ~255;

	/* Attributes which have gone off */
	e = ((AT_MASK|FG_NOT_DEFAULT|BG_NOT_DEFAULT)&t->attrib & ~c);

	if (e) {	/* If any attribute go off, switch them all off: fixes bug on PCs */
		if (t->me)
			texec(t->cap, t->me, 1, 0, 0, 0, 0);
		else {
			if (t->ue)
				texec(t->cap, t->ue, 1, 0, 0, 0, 0);
			if (t->se)
				texec(t->cap, t->se, 1, 0, 0, 0, 0);
		}
		t->attrib = 0;
	}

	/* Attributes which have turned on */
	e = (c & ~t->attrib);

	if (e & INVERSE) {
		if (t->mr)
			texec(t->cap, t->mr, 1, 0, 0, 0, 0);
		else if (t->so)
			texec(t->cap, t->so, 1, 0, 0, 0, 0);
	}

	if (e & UNDERLINE)
		if (t->us)
			texec(t->cap, t->us, 1, 0, 0, 0, 0);
	if (e & BLINK)
		if (t->mb)
			texec(t->cap, t->mb, 1, 0, 0, 0, 0);
	if (e & BOLD)
		if (t->md)
			texec(t->cap, t->md, 1, 0, 0, 0, 0);
	if (e & DIM)
		if (t->mh)
			texec(t->cap, t->mh, 1, 0, 0, 0, 0);

	if ((t->attrib & FG_MASK) != (c & FG_MASK)) {
		if (t->Sf) {
			int color = ((c & FG_VALUE) >> FG_SHIFT);
			if (t->assume_256 && color >= t->Co) {
				unsigned char bf[32];
				joe_snprintf_1(bf,sizeof(bf),"\033[38;5;%dm",color);
				ttputs(bf);
			} else {
				if (t->Co & (t->Co - 1))
					texec(t->cap, t->Sf, 1, color % t->Co, 0, 0, 0);
				else
					texec(t->cap, t->Sf, 1, color & (t->Co - 1), 0, 0, 0);
			}
		}
	}

	if ((t->attrib & BG_MASK) != (c & BG_MASK)) {
		if (t->Sb) {
			int color = ((c & BG_VALUE) >> BG_SHIFT);
			if (t->assume_256 && color >= t->Co) {
				unsigned char bf[32];
				joe_snprintf_1(bf,sizeof(bf),"\033[48;5;%dm",color);
				ttputs(bf);
			} else {
				if (t->Co & (t->Co - 1))
					texec(t->cap, t->Sb, 1, color % t->Co, 0, 0, 0);
				else
					texec(t->cap, t->Sb, 1, color & (t->Co - 1), 0, 0, 0);
			}
		}
	}

	t->attrib = c;

	return 0;
}

/* Inserts a space character at the current cursor position, and maybe move
 * the cursor. The attr of the inserted character is undefined.
 *
 * The caller is responsible for modifying t->scrn and t->attr (possibly using
 * memmove()).
 *
 * Don't call this function unless t->have_ins in true.
 *
 * Don't call this function in the rightmost column unless t->ce is true.
 */
static void ninsert1(SCRN *t) {
	if (t->gtco > 0 && t->x == t->gtco - 1 && t->ce) {
		texec(t->cap, t->ce, 1, 0, 0, 0, 0);
	} else if (t->ic) {
		/* TODO(pts): Do we have to emit t->ip? */
		texec(t->cap, t->ic, 1, 0, 0, 0, 0);
	      overwrite_null:
		if (t->in) {
			ttputc(' ');
			++t->x;
		}
	} else if (t->IC) {
        	texec(t->cap, t->IC, 1, 1, 0, 0, 0);
        	goto overwrite_null;
	} else if (t->im && t->ei) {
		texec(t->cap, t->im, 1, 0, 0, 0, 0);
		ttputc(' ');  /* Moves the cursor. */
		++t->x;
		texec(t->cap, t->ei, 1, 0, 0, 0, 0);
	} else {
		abort();
	}
}

/* Is the insertion-based workaround needed when printing a character so
 * that the cursor would be at after_column after the print?
 */
static char is_insert_needed(SCRN *t, int after_column, int yy) {
	return (after_column == t->gtco && t->gtco > 0 &&  /* Attempt to print to the rightmost column of the terminal. */
	        (t->wrap_mode == 1 ||  /* We use insertion to do the rightmost print. */
	         (t->wrap_mode == 2 && yy == t->gtli - 1)));  /* We use insertion only in the bottom line to do the rightmost print. */
}

/* Output character with attributes */
void outatr(struct charmap *map,SCRN *t,int *scrn,int *attrf,int xx,int yy,int c,int a)
{
	int control_attrs = 0;
	int wid, len;
	unsigned char buf[12];
	char do_insert;
	/* assert(xx < t->co); */
	if(map->type) {
		if(locale_map->type) {  /* UTF-8 char to UTF-8 terminal */
			int uni_ctrl = 0;

			/* Deal with control characters */
			if (c<32) {
				c = c + '@';
				a ^= UNDERLINE;
			} else if (c==127) {
				c = '?';
				a ^= UNDERLINE;
			} else if (unictrl(c)) {
				a ^= UNDERLINE;
				uni_ctrl = 1;
			}

			if (uni_ctrl) {
				len = sprintf((char *)buf, "<%X>", c & (int)0x7fffffff);
				wid = joe_wcwidth(1, c);
				while (len < wid) {  /* Must never happen, joe_wcwidth() is designed to return the right width. */
					buf[len++] = '~';
				}
				if (xx + wid > t->co)  /* Truncate the hexdump to the rightmost column of the terminal. */
					wid = t->co - xx;
				buf[wid] = '\0';  /* Failsafe for ttputs. */
				len = 0;
				while (len < wid && scrn[len] == buf[len] && attrf[len] == a) {
					++len;
				}
				if (len == wid)
					return;
				for (; len < wid; ++len) {
					scrn[len] = buf[len];
					attrf[len] = a;
				}
			} else {
				/* Now c != 0 (so it's safe to call ttputs), it's escaped as a control character above. */
				if(*scrn==c && *attrf==a)
					return;
				wid = joe_wcwidth(1, c);
				utf8_encode(buf, c);
				/* Now strlen(buf) might be more than wid,
				 * typically wid == 1 and strlen(buf) >= 2
				 * for latin accented letters.
				 */
			      print_wide:  /* Print (c, a, buf) when wid > 0. */
				*scrn = c;
				*attrf = a;
				for (len = wid; --len > 0; ) {
					scrn[len] = -1;
					attrf[len] = 0;
				}
			}

			if (0 != (do_insert = is_insert_needed(t, xx + wid, yy))) {
				--xx;
			}
		      print_wide_ca:
			if (t->x != xx || t->y != yy)
				cpos(t, xx, yy);
			if (t->attrib != a)
				set_attr(t, a);
			ttputs(buf);
			t->x += wid;
			if (do_insert) {
				cpos(t, xx, yy);
				/* We might insert to a middle of a wide char
				 * here. Both xterm and TERM=linux allow this,
				 * and they split or scramble the multibyte
				 * character, without scrambling other parts of
				 * the screen. Good.
				 */
				ninsert1(t);
				--scrn;
				--attrf;
				while (xx > 0 && *scrn == -1) { /* Skip over multibyte character. */
					--xx;
					--scrn;
					--attrf;
				}
				c = *scrn;
				a = *attrf;
				do_insert = 0;
				wid = joe_wcwidth(1, c);
				utf8_encode(buf, c);
				goto print_wide_ca;  /* Re-print the character ruined by the insert above. */
			}
		} else {
		      print_utf8_to_single:
			/* UTF-8 char to non-UTF-8 terminal */
			/* Don't convert control chars below 256 */

			if (c < 0 || unictrl(c)) {
				if ((c & ~0xFF) == 0) {
					control_attrs |= xlata[c];
					c = xlatc[c];
				} else {
					control_attrs |= UNDERLINE;
					c = '*';
				}
			}

			c = from_uni(locale_map,c);
			if (c == -1) {
				c = '#';
				control_attrs |= UNDERLINE;
			}

			/* Deal with control characters */
			if (!joe_isprint(locale_map,c)) {
				control_attrs |= xlata[c];
				c = xlatc[c];
			}
			a ^= control_attrs;

			if(*scrn==c && *attrf==a)
				return;

			*scrn = c;
			*attrf = a;
			if (0 != (do_insert = is_insert_needed(t, xx + 1, yy))) {
				--xx;
			}
		      print_single_ca:
			if (t->x != xx || t->y != yy)
				cpos(t,xx,yy);
			if (t->attrib != a)
				set_attr(t, a);
			ttputc(c);
			t->x++;
			if (do_insert) {
				cpos(t, xx, yy);
				ninsert1(t);
				c = *--scrn;
				a = *--attrf;
				do_insert = 0;
				goto print_single_ca;  /* Re-print the character ruined by the insert above. */
			}


		}
	} else {
		if (!locale_map->type) {
			/* Non-UTF-8 char to non-UTF-8 terminal */
			/* Translate from map to Unicode to locale_map */

			if (!joe_isprint(map,c)) {
				control_attrs |= xlata[c];
				c = xlatc[c];
			} else {
				c = to_uni(map,c);
				if (c == -1) {
					c = ':';
					control_attrs |= UNDERLINE;
				}
			}
			goto print_utf8_to_single;
		} else {
			/* Non-UTF-8 char to UTF-8 terminal */
			/* TODO(pts): Print multibyte characters (e.g. <DFF0>) if possible; also modify lgen() in bw.c (near `utf8_char = bc') calling outatr() so it knows the width. */

			/* Deal with control characters */
			if (!joe_isprint(map,c)) {
				control_attrs |= xlata[c];
				c = xlatc[c];
			} else {
				c = to_uni(map,c);
				if (c == -1) {
					c = '#';
					control_attrs |= UNDERLINE;
				} else if (!joe_isprint(locale_map, c)) {
					control_attrs |= UNDERLINE;
					c = '%';
				} else if (unictrl(c)) {
					control_attrs |= UNDERLINE;
					c = '|';
				}
			}
			a ^= control_attrs;
			if (*scrn == c && *attrf == a)
				return;
			wid = joe_wcwidth(0, c);  /* This always returns 1 because the 1st argument of joe_wcwidth is 0. */
			utf8_encode(buf,c);
			goto print_wide;
		}
	}

	/* If we've just written to the last column, and the terminal didn't
	 * wrap (because it has LP or xn), then we move the cursor to a safe
	 * position so unexpected wrappings won't happen.
	 */
	if (t->x == t->gtco && t->gtco > 0 && t->wrap_mode >= 2) {
		ttputc('\r');  /* Move cursor to the beginning of the line. */
		t->x = 0;
	}
}

/* Set scrolling region */

static void setregn(SCRN *t, int top, int bot)
{
	if (!t->cs) {
		t->top = top;
		t->bot = bot;
		return;
	}
	if (t->top != top || t->bot != bot) {
		t->top = top;
		t->bot = bot;
		texec(t->cap, t->cs, 1, top, bot - 1, 0, 0);
		t->x = -1;
		t->y = -1;
	}
}

/* Erase from given screen coordinate to end of line */

int eraeol(SCRN *t, int x, int y, int atr)
{
	int *s, *ss, *a, *aa;
	int w = t->co - x;

	if (w <= 0)
		return 0;
	s = t->scrn + y * t->co + x;
	a = t->attr + y * t->co + x;
	ss = s + w;  /* Start of line (y + 1) */
	aa = a + w;
	
	do {
		if (*--ss != ' ') {
			++ss;
			break;
		} else if (*--aa != atr) {
			++ss;
			++aa;
			break;
		}
	} while (ss != s);
	cpos(t, x, y);
	if ((ss - s > 3 ||  /* Too many columns to clear manually. */
	     t->gtco > t->co ||  /* Terminal is wider than what joe uses. */
	     (t->gtco == t->co && ss == s + w)  /* (t->wrap_mode != 0) Rightmost column of terminal to be cleared. */
	    ) && t->ce) {
		if(t->attrib != atr)
			set_attr(t, atr); 
		texec(t->cap, t->ce, 1, 0, 0, 0, 0);
		msetI(s, ' ', w);
		msetI(a, atr, w);
	} else if (s != ss) {
		if (t->attrib != atr)
			set_attr(t, atr); 
		while (s != ss) {
			*s++ = ' ';
			*a++ = atr;
			ttputc(' ');
			++t->x;
		}
	}
	return 0;
}

/* As above but useable in insert mode */
/* The cursor position must already be correct */

static void out(unsigned char *t, unsigned char c)
{
	ttputc(c);
}

SCRN *nopen(CAP *cap)
{
	SCRN *t = (SCRN *) joe_malloc(sizeof(SCRN));
	int wid, hei;
	char is_from_ttgtsz;

	ttopen();

	t->cap = cap;
	setcap(cap, baud, out, NULL);

	/* We don't set `t->co = wid' and `to->li = hei' here, but we'll do
	 * it in nresize called below.
	 */
	wid = hei = 0;
	ttgtsz(&wid, &hei);
	if (!(is_from_ttgtsz = (wid > 7 && hei > 3))) {
		hei = getnum(t->cap,USTR "li");
		if (hei < 1)
			hei = 24;
		wid = getnum(t->cap,USTR "co");
		if (wid < 2)
			wid = 80;
	}

	t->haz = getflag(t->cap,USTR "hz");
	t->os = getflag(t->cap,USTR "os");
	t->eo = getflag(t->cap,USTR "eo");
	if (getflag(t->cap,USTR "hc"))
		t->os = 1;
	if (t->os || getflag(t->cap,USTR "ul"))
		t->ul = 1;
	else
		t->ul = 0;

	t->am = getflag(t->cap,USTR "am");
	t->xn = getflag(t->cap,USTR "xn");
	t->LP = getflag(t->cap,USTR "LP");

	if (notite)
		t->ti = 0;
	else
		t->ti = jgetstr(t->cap,USTR "ti");
	t->cl = jgetstr(t->cap,USTR "cl");
	t->cd = jgetstr(t->cap,USTR "cd");

	if (notite)
		t->te = 0;
	else
		t->te = jgetstr(t->cap,USTR "te");

	t->brp = USTR "\033[?2004h";
	t->bre = USTR "\033[?2004l";

	t->ut = getflag(t->cap,USTR "ut");
	t->Sb = jgetstr(t->cap,USTR "AB");
	if (!t->Sb) t->Sb = jgetstr(t->cap,USTR "Sb");
	t->Sf = jgetstr(t->cap,USTR "AF");
	if (!t->Sf) t->Sf = jgetstr(t->cap,USTR "Sf");
	t->Co = getnum(t->cap,USTR "Co");
	if (t->Co == -1)
		t->Co = 8;

	t->mb = NULL;
	t->md = NULL;
	t->mh = NULL;
	t->mr = NULL;
	t->avattr = 0;
	if (!(t->me = jgetstr(t->cap,USTR "me")))
		goto oops;
	if ((t->mb = jgetstr(t->cap,USTR "mb")))
		t->avattr |= BLINK;
	if ((t->md = jgetstr(t->cap,USTR "md")))
		t->avattr |= BOLD;
	if ((t->mh = jgetstr(t->cap,USTR "mh")))
		t->avattr |= DIM;
	if ((t->mr = jgetstr(t->cap,USTR "mr")))
		t->avattr |= INVERSE;
      oops:


	if (assume_color || assume_256color) {
		/* Install 8 color support if it looks like an ansi terminal (it has bold which begins with ESC [) */
#ifndef TERMINFO
		if (!t->Sf && t->md && t->md[0]=='\\' && t->md[1]=='E' && t->md[2]=='[') { 
			t->ut = 1;
			t->Sf = USTR "\\E[3%dm";
			t->Sb = USTR "\\E[4%dm";
			t->Co = 8;
		}
#else
		if (!t->Sf && t->md && t->md[0]=='\033' && t->md[1]=='[') { 
			t->ut = 1;
			t->Sf = USTR "\033[3%p1%dm";
			t->Sb = USTR "\033[4%p1%dm";
		}
#endif
	}

	t->assume_256 = 0;
      	if (assume_256color && t->Co < 256) {
		/* Force 256 color support */
#ifndef TERMINFO
		if (t->md && t->md[0]=='\\' && t->md[1]=='E' && t->md[2]=='[') { 
			t->assume_256 = 1;
#ifdef junk
			t->ut = 1;
			t->Sf = USTR "\\E[38;5;%dm";
			t->Sb = USTR "\\E[48;5;%dm";
#endif
		}
#else
		if (t->md && t->md[0]=='\033' && t->md[1]=='[') { 
			t->assume_256 = 1;
#ifdef junk
			t->ut = 1;
			t->Sf = USTR "\033[38;5;%p1%dm";
			t->Sb = USTR "\033[48;5;%p1%dm";
#endif
		}
#endif
	}

	t->so = NULL;
	t->se = NULL;
	if (getnum(t->cap,USTR "sg") <= 0 && !t->mr && jgetstr(t->cap,USTR "se")) {
		if ((t->so = jgetstr(t->cap,USTR "so")) != NULL)
			t->avattr |= INVERSE;
		t->se = jgetstr(t->cap,USTR "se");
	}
	if (getflag(t->cap,USTR "xs") || getflag(t->cap,USTR "xt"))
		t->so = NULL;

	t->us = NULL;
	t->ue = NULL;
	if (getnum(t->cap,USTR "ug") <= 0 && jgetstr(t->cap,USTR "ue")) {
		if ((t->us = jgetstr(t->cap,USTR "us")) != NULL)
			t->avattr |= UNDERLINE;
		t->ue = jgetstr(t->cap,USTR "ue");
	}

	if (!(t->uc = jgetstr(t->cap,USTR "uc")))
		if (t->ul)
			t->uc =USTR "_";
	if (t->uc)
		t->avattr |= UNDERLINE;

	t->ms = getflag(t->cap,USTR "ms");

	t->da = getflag(t->cap,USTR "da");
	t->db = getflag(t->cap,USTR "db");
	t->cs = jgetstr(t->cap,USTR "cs");
	t->rr = getflag(t->cap,USTR "rr");
	t->sf = jgetstr(t->cap,USTR "sf");
	t->sr = jgetstr(t->cap,USTR "sr");
	t->SF = jgetstr(t->cap,USTR "SF");
	t->SR = jgetstr(t->cap,USTR "SR");
	t->al = jgetstr(t->cap,USTR "al");
	t->dl = jgetstr(t->cap,USTR "dl");
	t->AL = jgetstr(t->cap,USTR "AL");
	t->DL = jgetstr(t->cap,USTR "DL");
	if (!getflag(t->cap,USTR "ns") && !t->sf)
		t->sf =USTR "\12";

	/* Insert mode parameters. */
	t->in = getflag(t->cap,USTR "in");
	t->im = jgetstr(t->cap,USTR "im");
	t->ei = jgetstr(t->cap,USTR "ei");
	t->ic = jgetstr(t->cap,USTR "ic");
	t->IC = jgetstr(t->cap,USTR "IC");
	t->ip = jgetstr(t->cap,USTR "ip");

	t->bs = NULL;
	if (jgetstr(t->cap,USTR "bc"))
		t->bs = jgetstr(t->cap,USTR "bc");
	else if (jgetstr(t->cap,USTR "le"))
		t->bs = jgetstr(t->cap,USTR "le");
	if (getflag(t->cap,USTR "bs"))
		t->bs =USTR "\10";

	t->cbs = tcost(t->cap, t->bs, 1, 2, 2, 0, 0);

	t->lf =USTR "\12";
	if (jgetstr(t->cap,USTR "do"))
		t->lf = jgetstr(t->cap,USTR "do");
	t->clf = tcost(t->cap, t->lf, 1, 2, 2, 0, 0);

	t->up = jgetstr(t->cap,USTR "up");
	t->cup = tcost(t->cap, t->up, 1, 2, 2, 0, 0);

	t->nd = jgetstr(t->cap,USTR "nd");

	t->tw = 8;
	if (getnum(t->cap,USTR "it") > 0)
		t->tw = getnum(t->cap,USTR "it");
	else if (getnum(t->cap,USTR "tw") > 0)
		t->tw = getnum(t->cap,USTR "tw");

	if (!(t->ta = jgetstr(t->cap,USTR "ta")))
		if (getflag(t->cap,USTR "pt"))
			t->ta =USTR "\11";
	t->bt = jgetstr(t->cap,USTR "bt");
	if (getflag(t->cap,USTR "xt")) {
		t->ta = NULL;
		t->bt = NULL;
	}

	if (!usetabs) {
		t->ta = NULL;
		t->bt = NULL;
	}

	t->cta = tcost(t->cap, t->ta, 1, 2, 2, 0, 0);
	t->cbt = tcost(t->cap, t->bt, 1, 2, 2, 0, 0);

	t->ho = jgetstr(t->cap,USTR "ho");
	t->cho = tcost(t->cap, t->ho, 1, 2, 2, 0, 0);
	t->ll = jgetstr(t->cap,USTR "ll");
	t->cll = tcost(t->cap, t->ll, 1, 2, 2, 0, 0);

	t->cr =USTR "\15";
	if (jgetstr(t->cap,USTR "cr"))
		t->cr = jgetstr(t->cap,USTR "cr");
	if (getflag(t->cap,USTR "nc") || getflag(t->cap,USTR "xr"))
		t->cr = NULL;
	t->ccr = tcost(t->cap, t->cr, 1, 2, 2, 0, 0);

	t->cRI = tcost(t->cap, t->RI = jgetstr(t->cap,USTR "RI"), 1, 2, 2, 0, 0);
	t->cLE = tcost(t->cap, t->LE = jgetstr(t->cap,USTR "LE"), 1, 2, 2, 0, 0);
	t->cUP = tcost(t->cap, t->UP = jgetstr(t->cap,USTR "UP"), 1, 2, 2, 0, 0);
	t->cDO = tcost(t->cap, t->DO = jgetstr(t->cap,USTR "DO"), 1, 2, 2, 0, 0);
	t->cch = tcost(t->cap, t->ch = jgetstr(t->cap,USTR "ch"), 1, 2, 2, 0, 0);
	t->ccv = tcost(t->cap, t->cv = jgetstr(t->cap,USTR "cv"), 1, 2, 2, 0, 0);
	t->ccV = tcost(t->cap, t->cV = jgetstr(t->cap,USTR "cV"), 1, 2, 2, 0, 0);
	t->ccm = tcost(t->cap, t->cm = jgetstr(t->cap,USTR "cm"), 1, 2, 2, 0, 0);

	t->cce = tcost(t->cap, t->ce = jgetstr(t->cap,USTR "ce"), 1, 2, 2, 0, 0);

/* Make sure terminal can do absolute positioning */
	if (t->cm)
		goto ok;
	if (t->ch && t->cv)
		goto ok;
	if (t->ho && (t->lf || t->DO || t->cv))
		goto ok;
	if (t->ll && (t->up || t->UP || t->cv))
		goto ok;
	if (t->cr && t->cv)
		goto ok;
	leave = 1;
	ttclose();
	signrm();
        fprintf(stderr,"cm=%p ch=%p cv=%p ho=%p lf=%p DO=%p ll=%p up=%p UP=%p cr=%p\n",
                       t->cm, t->ch, t->cv, t->ho, t->lf, t->DO, t->ll, t->up, t->UP, t->cr);
	fprintf(stderr,(char *)joe_gettext(_("Sorry, your terminal can't do absolute cursor positioning.\nIt's broken\n")));
	return NULL;
      ok:

/* Determine if we can scroll */
	if (((t->sr || t->SR) && (t->sf || t->SF) && t->cs) || ((t->al || t->AL) && (t->dl || t->DL)))
		t->scroll = 1;
	else {
		t->scroll = 0;
		if (baud < 38400)
			mid = 1;
	}

	t->have_ins = (t->im && t->ei && t->ce) || t->ic || t->IC;

/* Adjust for high baud rates */
	if (baud >= 38400) {
		t->scroll = 0;
	}

/* Send out terminal initialization string */
	if (t->ti)
		texec(t->cap, t->ti, 1, 0, 0, 0, 0);
	if (!skiptop && t->cl)
		texec(t->cap, t->cl, 1, 0, 0, 0, 0);
	if (t->brp)
		texec(t->cap, t->brp, 1, 0, 0, 0, 0);

/* Initialize variable screen size dependant vars */
	t->wrap_mode = t->li = t->co = t->gtli = t->gtco = 0;
	t->scrn = NULL;
	t->attr = NULL;
	t->sary = NULL;
	t->updtab = NULL;
	t->compose = NULL;
	t->ofst = NULL;
	t->ary = NULL;
	t->htab = (struct hentry *) joe_malloc(256 * sizeof(struct hentry));
	nresize(t, wid, hei, is_from_ttgtsz);

/* Initialize mouse */
	mouseopen();

	return t;
}

int nresize(SCRN *t, int wid, int hei, char is_from_ttgtsz)
{
	char has_gtli_changed = 0;
	if (is_from_ttgtsz) {
		if (wid > 0 && hei > 0) {
			if (t->gtli != hei && t->gtli > 0)
				has_gtli_changed = 1;
			t->gtli = hei;
			t->gtco = wid;
		} else {
			t->gtli = t->gtco = 0;
		}
	}
	if (env_lines > 0)
		hei = env_lines;
	if (env_columns > 0)
		wid = env_columns;
	if (hei < 4)
		hei = 4;
	if (wid < 8)
		wid = 8;
	t->wrap_mode = 0;
	if (t->gtco >= 8) {
		if (wid >= t->gtco) {
			wid = t->gtco;
			/* We need t->ce in wrap_mode for eraeol(). */
			/* These `if' branches are in decreasing order of
			 * simplicity and required bandwidth to the terminal.
			 */
			if (t->ce && t->LP) {
				t->wrap_mode = 3;
			} else if (t->ce && t->xn && t->have_ins) {
				t->wrap_mode = 2;
			} else if (t->ce && t->have_ins) {
				t->wrap_mode = 1;
			} else {
				--wid;
			}
		}
	} else {
		/* Don't write to the rightmost column, because we can't
		 * guarantee that the cursor won't wrap and the screen won't
		 * scroll.
		 */
		--wid;
	}
	if (t->gtli >= 4 && hei > t->gtli) {
		hei = t->gtli;
	}

	if (t->li == hei && t->co == wid) {
		/* If the number of lines has changed since the last ttgtsz,
		 * the terminal (e.g. xterm) might have scrolled the current
		 * screen contents, so we'd better redraw.
		 */
		if (has_gtli_changed && t->scrn != NULL)
			nredraw(t);
		return 0;
	}
	t->li = hei;
	t->co = wid;
	if (t->sary)
		joe_free(t->sary);
	if (t->updtab)
		joe_free(t->updtab);
	if (t->scrn)
		joe_free(t->scrn);
	if (t->attr)
		joe_free(t->attr);
	if (t->compose)
		joe_free(t->compose);
	if (t->ofst)
		joe_free(t->ofst);
	if (t->ary)
		joe_free(t->ary);
	t->scrn = (int *) joe_malloc(t->li * t->co * sizeof(int));
	t->attr = (int *) joe_malloc(t->li * t->co * sizeof(int));
	t->sary = (int *) joe_calloc(t->li, sizeof(int));
	t->updtab = (int *) joe_malloc(t->li * sizeof(int));
	t->compose = (int *) joe_malloc(t->co * sizeof(int));
	t->ofst = (int *) joe_malloc(t->co * sizeof(int));
	t->ary = (struct hentry *) joe_malloc(t->co * sizeof(struct hentry));

	nredraw(t);
	return 1;
}

/* Calculate cost of positioning the cursor using only relative cursor
 * positioning functions: t->(lf, DO, up, UP, bs, LE, RI, ta, bt) and rewriting
 * characters (to move right)
 *
 * This doesn't use the am and bw capabilities although it probably could.
 */

static int relcost(register SCRN *t, register int x, register int y, register int ox, register int oy)
{
	int cost = 0;

/* If we don't know the cursor position, force use of absolute positioning */
	if (oy == -1 || ox == -1)
		return 10000;

/* First adjust row */
	if (y > oy) {
		int dist = y - oy;

		/* Have to go down */
		if (t->lf) {
			int mult = dist * t->clf;

			if (dist < 10 && t->cDO < mult)
				cost += t->cDO;
			else if (dist >= 10 && t->cDO + 1 < mult)
				cost += t->cDO + 1;
			else
				cost += mult;
		} else if (t->DO)
			if (dist < 10)
				cost += t->cDO;
			else
				cost += t->cDO + 1;
		else
			return 10000;
	} else if (y < oy) {
		int dist = oy - y;

		/* Have to go up */
		if (t->up) {
			int mult = dist * t->cup;

			if (dist < 10 && t->cUP < mult)
				cost += t->cUP;
			else if (dist >= 10 && t->cUP < mult)
				cost += t->cUP + 1;
			else
				cost += mult;
		} else if (t->UP)
			if (dist < 10)
				cost += t->cUP;
			else
				cost += t->cUP + 1;
		else
			return 10000;
	}

/* Now adjust column */

/* Use tabs */
	if (x > ox && t->ta) {
		int dist = x - ox;
		int ntabs = (dist + ox % t->tw) / t->tw;
		int cstunder = x % t->tw + t->cta * ntabs;
		int cstover;

		if (x + t->tw < t->co && t->bs)
			cstover = t->cbs * (t->tw - x % t->tw) + t->cta * (ntabs + 1);
		else
			cstover = 10000;
		if (dist < 10 && cstunder < t->cRI && cstunder < x - ox && cstover > cstunder)
			return cost + cstunder;
		else if (cstunder < t->cRI + 1 && cstunder < x - ox && cstover > cstunder)
			return cost + cstunder;
		else if (dist < 10 && cstover < t->cRI && cstover < x - ox)
			return cost + cstover;
		else if (cstover < t->cRI + 1 && cstover < x - ox)
			return cost + cstover;
	} else if (x < ox && t->bt) {
		int dist = ox - x;
		int ntabs = (dist + t->tw - ox % t->tw) / t->tw;
		int cstunder, cstover;

		if (t->bs)
			cstunder = t->cbt * ntabs + t->cbs * (t->tw - x % t->tw);
		else
			cstunder = 10000;
		if (x - t->tw >= 0)
			cstover = t->cbt * (ntabs + 1) + x % t->tw;
		else
			cstover = 10000;
		if (dist < 10 && cstunder < t->cLE && (t->bs ? cstunder < (ox - x) * t->cbs : 1)
		    && cstover > cstunder)
			return cost + cstunder;
		if (cstunder < t->cLE + 1 && (t->bs ? cstunder < (ox - x) * t->cbs : 1)
		    && cstover > cstunder)
			return cost + cstunder;
		else if (dist < 10 && cstover < t->cRI && (t->bs ? cstover < (ox - x) * t->cbs : 1))
			return cost + cstover;
		else if (cstover < t->cRI + 1 && (t->bs ? cstover < (ox - x) * t->cbs : 1))
			return cost + cstover;
	}

/* Use simple motions */
	if (x < ox) {
		int dist = ox - x;

		/* Have to go left */
		if (t->bs) {
			int mult = dist * t->cbs;

			if (t->cLE < mult && dist < 10)
				cost += t->cLE;
			else if (t->cLE + 1 < mult)
				cost += t->cLE + 1;
			else
				cost += mult;
		} else if (t->LE)
			cost += t->cLE;
		else
			return 10000;
	} else if (x > ox) {
		int dist = x - ox;

		/* Have to go right */
		/* Hmm.. this should take into account possible attribute changes */
		if (t->cRI < dist && dist < 10)
			cost += t->cRI;
		else if (t->cRI + 1 < dist)
			cost += t->cRI + 1;
		else
			cost += dist;
	}

	return cost;
}

/* Find optimal set of cursor positioning commands to move from the current
 * cursor row and column (either or both of which might be unknown) to the
 * given new row and column and execute them.
 */

static void cposs(register SCRN *t, register int x, register int y)
{
	register int bestcost, cost;
	int bestway;
	int hy;
	int hl;

/* Home y position is usually 0, but it is 'top' if we have scrolling region
 * relative addressing
 */
	if (t->rr) {
		hy = t->top;
		hl = t->bot - 1;
	} else {
		hy = 0;
		hl = t->li - 1;
	}

/* Assume best way is with only using relative cursor positioning */

	bestcost = relcost(t, x, y, t->x, t->y);
	bestway = 0;

/* Now check if combinations of absolute cursor positioning functions are
 * better (or necessary in case one or both cursor positions are unknown)
 */

	if (t->ccm < bestcost) {
		cost = tcost(t->cap, t->cm, 1, y, x, 0, 0);
		if (cost < bestcost) {
			bestcost = cost;
			bestway = 6;
		}
	}
	if (t->ccr < bestcost) {
		cost = relcost(t, x, y, 0, t->y) + t->ccr;
		if (cost < bestcost) {
			bestcost = cost;
			bestway = 1;
		}
	}
	if (t->cho < bestcost) {
		cost = relcost(t, x, y, 0, hy) + t->cho;
		if (cost < bestcost) {
			bestcost = cost;
			bestway = 2;
		}
	}
	if (t->cll < bestcost) {
		cost = relcost(t, x, y, 0, hl) + t->cll;
		if (cost < bestcost) {
			bestcost = cost;
			bestway = 3;
		}
	}
	if (t->cch < bestcost && x != t->x) {
		cost = relcost(t, x, y, x, t->y) + tcost(t->cap, t->ch, 1, x, 0, 0, 0);
		if (cost < bestcost) {
			bestcost = cost;
			bestway = 4;
		}
	}
	if (t->ccv < bestcost && y != t->y) {
		cost = relcost(t, x, y, t->x, y) + tcost(t->cap, t->cv, 1, y, 0, 0, 0);
		if (cost < bestcost) {
			bestcost = cost;
			bestway = 5;
		}
	}
	if (t->ccV < bestcost) {
		cost = relcost(t, x, y, 0, y) + tcost(t->cap, t->cV, 1, y, 0, 0, 0);
		if (cost < bestcost) {
			bestcost = cost;
			bestway = 13;
		}
	}
	if (t->cch + t->ccv < bestcost && x != t->x && y != t->y) {
		cost = tcost(t->cap, t->cv, 1, y - hy, 0, 0, 0) + tcost(t->cap, t->ch, 1, x, 0, 0, 0);
		if (cost < bestcost) {
			bestcost = cost;
			bestway = 7;
		}
	}
	if (t->ccv + t->ccr < bestcost && y != t->y) {
		cost = tcost(t->cap, t->cv, 1, y, 0, 0, 0) + tcost(t->cap, t->cr, 1, 0, 0, 0, 0) + relcost(t, x, y, 0, y);
		if (cost < bestcost) {
			bestcost = cost;
			bestway = 8;
		}
	}
	if (t->cll + t->cch < bestcost) {
		cost = tcost(t->cap, t->ll, 1, 0, 0, 0, 0) + tcost(t->cap, t->ch, 1, x, 0, 0, 0) + relcost(t, x, y, x, hl);
		if (cost < bestcost) {
			bestcost = cost;
			bestway = 9;
		}
	}
	if (t->cll + t->ccv < bestcost) {
		cost = tcost(t->cap, t->ll, 1, 0, 0, 0, 0) + tcost(t->cap, t->cv, 1, y, 0, 0, 0) + relcost(t, x, y, 0, y);
		if (cost < bestcost) {
			bestcost = cost;
			bestway = 10;
		}
	}
	if (t->cho + t->cch < bestcost) {
		cost = tcost(t->cap, t->ho, 1, 0, 0, 0, 0) + tcost(t->cap, t->ch, 1, x, 0, 0, 0) + relcost(t, x, y, x, hy);
		if (cost < bestcost) {
			bestcost = cost;
			bestway = 11;
		}
	}
	if (t->cho + t->ccv < bestcost) {
		cost = tcost(t->cap, t->ho, 1, 0, 0, 0, 0) + tcost(t->cap, t->cv, 1, y, 0, 0, 0) + relcost(t, x, y, 0, y);
		if (cost < bestcost) {
			bestcost = cost;
			bestway = 12;
		}
	}

/* Do absolute cursor positioning if we don't know the cursor position or
 * if it is faster than doing only relative cursor positioning
 */

	switch (bestway) {
	case 1:
		texec(t->cap, t->cr, 1, 0, 0, 0, 0);
		t->x = 0;
		break;
	case 2:
		texec(t->cap, t->ho, 1, 0, 0, 0, 0);
		t->x = 0;
		t->y = hy;
		break;
	case 3:
		texec(t->cap, t->ll, 1, 0, 0, 0, 0);
		t->x = 0;
		t->y = hl;
		break;
	case 9:
		texec(t->cap, t->ll, 1, 0, 0, 0, 0);
		t->x = 0;
		t->y = hl;
		goto doch;
	case 11:
		texec(t->cap, t->ho, 1, 0, 0, 0, 0);
		t->x = 0;
		t->y = hy;
doch:
	case 4:
		texec(t->cap, t->ch, 1, x, 0, 0, 0);
		t->x = x;
		break;
	case 10:
		texec(t->cap, t->ll, 1, 0, 0, 0, 0);
		t->x = 0;
		t->y = hl;
		goto docv;
	case 12:
		texec(t->cap, t->ho, 1, 0, 0, 0, 0);
		t->x = 0;
		t->y = hy;
		goto docv;
	case 8:
		texec(t->cap, t->cr, 1, 0, 0, 0, 0);
		t->x = 0;
docv:
	case 5:
		texec(t->cap, t->cv, 1, y, 0, 0, 0);
		t->y = y;
		break;
	case 6:
		texec(t->cap, t->cm, 1, y, x, 0, 0);
		t->y = y;
		t->x = x;
		break;
	case 7:
		texec(t->cap, t->cv, 1, y, 0, 0, 0);
		t->y = y;
		texec(t->cap, t->ch, 1, x, 0, 0, 0);
		t->x = x;
		break;
	case 13:
		texec(t->cap, t->cV, 1, y, 0, 0, 0);
		t->y = y;
		t->x = 0;
		break;
	}

/* Use relative cursor position functions if we're not there yet */

/* First adjust row */
	if (y > t->y) {
		/* Have to go down */
		if (!t->lf || t->cDO < (y - t->y) * t->clf) {
			texec(t->cap, t->DO, 1, y - t->y, 0, 0, 0);
			t->y = y;
		} else
			while (y > t->y) {
				texec(t->cap, t->lf, 1, 0, 0, 0, 0);
				++t->y;
			}
	} else if (y < t->y) {
		/* Have to go up */
		if (!t->up || t->cUP < (t->y - y) * t->cup) {
			texec(t->cap, t->UP, 1, t->y - y, 0, 0, 0);
			t->y = y;
		} else
			while (y < t->y) {
				texec(t->cap, t->up, 1, 0, 0, 0, 0);
				--t->y;
			}
	}

/* Use tabs */
	if (x > t->x && t->ta) {
		int ntabs = (x - t->x + t->x % t->tw) / t->tw;
		int cstunder = x % t->tw + t->cta * ntabs;
		int cstover;

		if (x + t->tw < t->co && t->bs)
			cstover = t->cbs * (t->tw - x % t->tw) + t->cta * (ntabs + 1);
		else
			cstover = 10000;
		if (cstunder < t->cRI && cstunder < x - t->x && cstover > cstunder) {
			if (ntabs) {
				t->x = x - x % t->tw;
				do {
					texec(t->cap, t->ta, 1, 0, 0, 0, 0);
				} while (--ntabs);
			}
		} else if (cstover < t->cRI && cstover < x - t->x) {
			t->x = t->tw + x - x % t->tw;
			++ntabs;
			do {
				texec(t->cap, t->ta, 1, 0, 0, 0, 0);
			} while (--ntabs);
		}
	} else if (x < t->x && t->bt) {
		int ntabs = ((t->x + t->tw - 1) - (t->x + t->tw - 1) % t->tw - ((x + t->tw - 1) - (x + t->tw - 1) % t->tw)) / t->tw;
		int cstunder, cstover;

		if (t->bs)
			cstunder = t->cbt * ntabs + t->cbs * (t->tw - x % t->tw);
		else
			cstunder = 10000;
		if (x - t->tw >= 0)
			cstover = t->cbt * (ntabs + 1) + x % t->tw;
		else
			cstover = 10000;
		if (cstunder < t->cLE && (t->bs ? cstunder < (t->x - x) * t->cbs : 1)
		    && cstover > cstunder) {
			if (ntabs) {
				do {
					texec(t->cap, t->bt, 1, 0, 0, 0, 0);
				} while (--ntabs);
				t->x = x + t->tw - x % t->tw;
			}
		} else if (cstover < t->cRI && (t->bs ? cstover < (t->x - x) * t->cbs : 1)) {
			t->x = x - x % t->tw;
			++ntabs;
			do {
				texec(t->cap, t->bt, 1, 0, 0, 0, 0);
			} while (--ntabs);
		}
	}

/* Now adjust column */
	if (x < t->x) {
		/* Have to go left */
		if (!t->bs || t->cLE < (t->x - x) * t->cbs) {
			texec(t->cap, t->LE, 1, t->x - x, 0, 0, 0);
			t->x = x;
		} else
			while (x < t->x) {
				texec(t->cap, t->bs, 1, 0, 0, 0, 0);
				--t->x;
			}
	} else if (x > t->x) {
		/* Have to go right */
		/* Hmm.. this should take into account possible attribute changes */
		if (x-t->x>1 && t->RI) {
			texec(t->cap, t->RI, 1, x - t->x, 0, 0, 0);
			t->x = x;
		} else {
			while(x>t->x) {
				texec(t->cap, t->nd, 1, 0, 0, 0, 0);
				++t->x;
			}
		}
	}
}

int cpos(register SCRN *t, register int x, register int y)
{
	/* Move cursor quickly if we can */
	if (y == t->y) {
		if (x > t->x && x - t->x < 4) {
			int *cs = t->scrn + t->x + t->co * t->y;
			int *as = t->attr + t->x + t->co * t->y;
			do {
				/* We used to space over unknown chars, but they now could be
				   the right half of a UTF-8 two column character, so we can't.
				   Also do not try to emit utf-8 sequences here. */
				if(*cs<32 || *cs>=127)
					break;

				if (*as != t->attrib)
					set_attr(t, *as);

				ttputc(*cs);

				++cs;
				++as;
				++t->x;

			} while (x != t->x);
		}
		if (x == t->x)
			return 0;
	}
	if ((!t->ms && t->attrib & (INVERSE | UNDERLINE | BG_NOT_DEFAULT)) ||
	    (t->ut && (t->attrib & BG_NOT_DEFAULT)))
		set_attr(t, t->attrib & ~(INVERSE | UNDERLINE | BG_MASK));

	/* Should be in cposs */
	if (y < t->top || y >= t->bot)
		setregn(t, 0, t->li);

	cposs(t, x, y);
	return 0;
}

static void doupscrl(SCRN *t, int top, int bot, int amnt, int atr)
{
	int a = amnt;

	if (!amnt)
		return;
	set_attr(t, atr);
	if (top == 0 && bot == t->li && (t->sf || t->SF)) {
		setregn(t, 0, t->li);
		cpos(t, 0, t->li - 1);
		if ((amnt == 1 && t->sf) || !t->SF)
			while (a--)
				texec(t->cap, t->sf, 1, t->li - 1, 0, 0, 0);
		else
			texec(t->cap, t->SF, a, a, 0, 0, 0);
		goto done;
	}
	if (bot == t->li && (t->dl || t->DL)) {
		setregn(t, 0, t->li);
		cpos(t, 0, top);
		if ((amnt == 1 && t->dl) || !t->DL)
			while (a--)
				texec(t->cap, t->dl, 1, top, 0, 0, 0);
		else
			texec(t->cap, t->DL, a, a, 0, 0, 0);
		goto done;
	}
	if (t->cs && (t->sf || t->SF)) {
		setregn(t, top, bot);
		cpos(t, 0, bot - 1);
		if ((amnt == 1 && t->sf) || !t->SF)
			while (a--)
				texec(t->cap, t->sf, 1, bot - 1, 0, 0, 0);
		else
			texec(t->cap, t->SF, a, a, 0, 0, 0);
		goto done;
	}
	if ((t->dl || t->DL) && (t->al || t->AL)) {
		cpos(t, 0, top);
		if ((amnt == 1 && t->dl) || !t->DL)
			while (a--)
				texec(t->cap, t->dl, 1, top, 0, 0, 0);
		else
			texec(t->cap, t->DL, a, a, 0, 0, 0);
		a = amnt;
		cpos(t, 0, bot - amnt);
		if ((amnt == 1 && t->al) || !t->AL)
			while (a--)
				texec(t->cap, t->al, 1, bot - amnt, 0, 0, 0);
		else
			texec(t->cap, t->AL, a, a, 0, 0, 0);
		goto done;
	}
	msetI(t->updtab + top, 1, bot - top);
	return;

      done:
	memmove(t->scrn + top * t->co, t->scrn + (top + amnt) * t->co, (bot - top - amnt) * t->co * sizeof(int));
	memmove(t->attr + top * t->co, t->attr + (top + amnt) * t->co, (bot - top - amnt) * t->co * sizeof(int));

	if (bot == t->li && t->db) {
		msetI(t->scrn + (t->li - amnt) * t->co, -1, amnt * t->co);
		msetI(t->attr + (t->li - amnt) * t->co, 0, amnt * t->co);
		msetI(t->updtab + t->li - amnt, 1, amnt);
	} else {
		msetI(t->scrn + (bot - amnt) * t->co, ' ', amnt * t->co);
		msetI(t->attr + (bot - amnt) * t->co, 0, amnt * t->co); 
	}
}

static void dodnscrl(SCRN *t, int top, int bot, int amnt, int atr)
{
	int a = amnt;

	if (!amnt)
		return;
	set_attr(t, atr); 
	if (top == 0 && bot == t->li && (t->sr || t->SR)) {
		setregn(t, 0, t->li);
		cpos(t, 0, 0);
		if ((amnt == 1 && t->sr) || !t->SR)
			while (a--)
				texec(t->cap, t->sr, 1, 0, 0, 0, 0);
		else
			texec(t->cap, t->SR, a, a, 0, 0, 0);
		goto done;
	}
	if (bot == t->li && (t->al || t->AL)) {
		setregn(t, 0, t->li);
		cpos(t, 0, top);
		if ((amnt == 1 && t->al) || !t->AL)
			while (a--)
				texec(t->cap, t->al, 1, top, 0, 0, 0);
		else
			texec(t->cap, t->AL, a, a, 0, 0, 0);
		goto done;
	}
	if (t->cs && (t->sr || t->SR)) {
		setregn(t, top, bot);
		cpos(t, 0, top);
		if ((amnt == 1 && t->sr) || !t->SR)
			while (a--)
				texec(t->cap, t->sr, 1, top, 0, 0, 0);
		else
			texec(t->cap, t->SR, a, a, 0, 0, 0);
		goto done;
	}
	if ((t->dl || t->DL) && (t->al || t->AL)) {
		cpos(t, 0, bot - amnt);
		if ((amnt == 1 && t->dl) || !t->DL)
			while (a--)
				texec(t->cap, t->dl, 1, bot - amnt, 0, 0, 0);
		else
			texec(t->cap, t->DL, a, a, 0, 0, 0);
		a = amnt;
		cpos(t, 0, top);
		if ((amnt == 1 && t->al) || !t->AL)
			while (a--)
				texec(t->cap, t->al, 1, top, 0, 0, 0);
		else
			texec(t->cap, t->AL, a, a, 0, 0, 0);
		goto done;
	}
	msetI(t->updtab + top, 1, bot - top);
	return;
      done:
	memmove(t->scrn + (top + amnt) * t->co, t->scrn + top * t->co, (bot - top - amnt) * t->co * sizeof(int));
	memmove(t->attr + (top + amnt) * t->co, t->attr + top * t->co, (bot - top - amnt) * t->co * sizeof(int));

	if (!top && t->da) {
		msetI(t->scrn, -1, amnt * t->co);
		msetI(t->attr, 0, amnt * t->co);
		msetI(t->updtab, 1, amnt);
	} else {
		msetI(t->scrn + t->co * top, ' ', amnt * t->co);
		msetI(t->attr + t->co * top, 0, amnt * t->co); 
	}
}

void nscroll(SCRN *t,int atr)
{
	int y, z, q, r, p;

	for (y = 0; y != t->li; ++y) {
		q = t->sary[y];
		if (ifhave)
			return;
		if (q && q != t->li) {
			if (q > 0) {
				for (z = y; z != t->li && t->sary[z] == q; ++z)
					t->sary[z] = 0;
				doupscrl(t, y, z + q, q, atr);
				y = z - 1;
			} else {
				for (r = y; r != t->li && (t->sary[r] < 0 || t->sary[r] == t->li); ++r) ;
				p = r - 1;
				do {
					q = t->sary[p];
					if (q && q != t->li) {
						for (z = p; t->sary[z] = 0, (z && t->sary[z - 1] == q); --z) ;
						dodnscrl(t, z + q, p + 1, -q, atr);
						p = z + 1;
					}
				} while (p-- != y);
				y = r - 1;
			}
		}
	}
	msetI(t->sary, 0, t->li);
}

void npartial(SCRN *t)
{
	set_attr(t, BG_COLOR(bg_text)); 
	setregn(t, 0, t->li);
}

void nescape(SCRN *t)
{
	mouseclose();
	npartial(t);
	cpos(t, 0, t->li - 1);
	eraeol(t, 0, t->li - 1, 0);
	if (t->bre)
		texec(t->cap, t->bre, 1, 0, 0, 0, 0);
	if (t->te)
		texec(t->cap, t->te, 1, 0, 0, 0, 0);
}

void nreturn(SCRN *t)
{
	mouseopen();
	if (t->ti)
		texec(t->cap, t->ti, 1, 0, 0, 0, 0);
	if (!skiptop && t->cl)
		texec(t->cap, t->cl, 1, 0, 0, 0, 0);
	if (t->brp)
		texec(t->cap, t->brp, 1, 0, 0, 0, 0);
	nredraw(t);
}

void nclose(SCRN *t)
{
	mouseclose();
	leave = 1;
	set_attr(t, 0);
	setregn(t, 0, t->li);
	cpos(t, 0, t->li - 1);
	if (t->bre)
		texec(t->cap, t->bre, 1, 0, 0, 0, 0);
	if (t->te)
		texec(t->cap, t->te, 1, 0, 0, 0, 0);
	ttclose();
	rmcap(t->cap);
	joe_free(t->scrn);
	joe_free(t->attr);
	joe_free(t->sary);
	joe_free(t->ofst);
	joe_free(t->htab);
	joe_free(t->ary);
	joe_free(t);
}

void nscrldn(SCRN *t, int top, int bot, int amnt)
{
	int x;

	if (!amnt || top >= bot || bot > t->li)
		return;
	if ((amnt < bot - top && bot - top - amnt < amnt / 2) || !t->scroll)
		amnt = bot - top;
	if (amnt < bot - top) {
		for (x = bot; x != top + amnt; --x) {
			t->sary[x - 1] = (t->sary[x - amnt - 1] == t->li ? t->li : t->sary[x - amnt - 1] - amnt);
			t->updtab[x - 1] = t->updtab[x - amnt - 1];
		}
		for (x = top; x != top + amnt; ++x) {
			t->updtab[x] = 1;
		}
	}
	if (amnt > bot - top)
		amnt = bot - top;
	msetI(t->sary + top, t->li, amnt);
	if (amnt == bot - top) {
		msetI(t->updtab + top, 1, amnt);
	}
}

void nscrlup(SCRN *t, int top, int bot, int amnt)
{
	int x;

	if (!amnt || top >= bot || bot > t->li)
		return;
	if ((amnt < bot - top && bot - top - amnt < amnt / 2) || !t->scroll)
		amnt = bot - top;
	if (amnt < bot - top) {
		for (x = top + amnt; x != bot; ++x) {
			t->sary[x - amnt] = (t->sary[x] == t->li ? t->li : t->sary[x] + amnt);
			t->updtab[x - amnt] = t->updtab[x];
		}
		for (x = bot - amnt; x != bot; ++x) {
			t->updtab[x] = 1;
		}
	}
	if (amnt > bot - top)
		amnt = bot - top;
	msetI(t->sary + bot - amnt, t->li, amnt);
	if (amnt == bot - top) {
		msetI(t->updtab + bot - amnt, 1, amnt);
		}
}

void nredraw(SCRN *t)
{
	dostaupd = 1;
	msetI(t->scrn, ' ', t->co * skiptop);
	msetI(t->attr, BG_COLOR(bg_text), t->co * skiptop);  
	msetI(t->scrn + skiptop * t->co, -1, (t->li - skiptop) * t->co);
	msetI(t->attr + skiptop * t->co, BG_COLOR(bg_text), (t->li - skiptop) * t->co); 
	msetI(t->sary, 0, t->li);
	msetI(t->updtab + skiptop, -1, t->li - skiptop);
	t->x = -1;
	t->y = -1;
	t->top = t->li;
	t->bot = 0;
	t->attrib = -1;
	set_attr(t, BG_COLOR(bg_text)); 
	texec(t->cap, t->ei, 1, 0, 0, 0, 0);  /* Exit from insert mode. */
	setregn(t, 0, t->li);

	if (!skiptop) {
		if (t->cl) {
			texec(t->cap, t->cl, 1, 0, 0, 0, 0);
			t->x = 0;
			t->y = 0;
			msetI(t->scrn, ' ', t->li * t->co);
			msetI(t->attr, BG_COLOR(bg_text), t->li * t->co); 
		} else if (t->cd) {
			cpos(t, 0, 0);
			texec(t->cap, t->cd, 1, 0, 0, 0, 0);
		}
		msetI(t->scrn, ' ', t->li * t->co);
		msetI(t->attr, BG_COLOR(bg_text), t->li * t->co); 
	}
}

/* Convert color/attribute name into internal code */

int meta_color_single(unsigned char *s)
{
	if(!zcmp(s,USTR "inverse"))
		return INVERSE;
	else if(!zcmp(s,USTR "underline"))
		return UNDERLINE;
	else if(!zcmp(s,USTR "bold"))
		return BOLD;
	else if(!zcmp(s,USTR "blink"))
		return BLINK;
	else if(!zcmp(s,USTR "dim"))
		return DIM;

	/* ISO colors */
	else if(!zcmp(s,USTR "white"))
		return FG_WHITE;
	else if(!zcmp(s,USTR "cyan"))
		return FG_CYAN;
	else if(!zcmp(s,USTR "magenta"))
		return FG_MAGENTA;
	else if(!zcmp(s,USTR "blue"))
		return FG_BLUE;
	else if(!zcmp(s,USTR "yellow"))
		return FG_YELLOW;
	else if(!zcmp(s,USTR "green"))
		return FG_GREEN;
	else if(!zcmp(s,USTR "red"))
		return FG_RED;
	else if(!zcmp(s,USTR "black"))
		return FG_BLACK;
	else if(!zcmp(s,USTR "bg_white"))
		return BG_WHITE;
	else if(!zcmp(s,USTR "bg_cyan"))
		return BG_CYAN;
	else if(!zcmp(s,USTR "bg_magenta"))
		return BG_MAGENTA;
	else if(!zcmp(s,USTR "bg_blue"))
		return BG_BLUE;
	else if(!zcmp(s,USTR "bg_yellow"))
		return BG_YELLOW;
	else if(!zcmp(s,USTR "bg_green"))
		return BG_GREEN;
	else if(!zcmp(s,USTR "bg_red"))
		return BG_RED;
	else if(!zcmp(s,USTR "bg_black"))
		return BG_BLACK;

	/* 16 color xterm support: codes 8 - 15 are brighter versions of above */
	else if(!zcmp(s,USTR "WHITE"))
		return FG_BWHITE;
	else if(!zcmp(s,USTR "CYAN"))
		return FG_BCYAN;
	else if(!zcmp(s,USTR "MAGENTA"))
		return FG_BMAGENTA;
	else if(!zcmp(s,USTR "BLUE"))
		return FG_BBLUE;
	else if(!zcmp(s,USTR "YELLOW"))
		return FG_BYELLOW;
	else if(!zcmp(s,USTR "GREEN"))
		return FG_BGREEN;
	else if(!zcmp(s,USTR "RED"))
		return FG_BRED;
	else if(!zcmp(s,USTR "BLACK"))
		return FG_BBLACK;
	else if(!zcmp(s,USTR "bg_WHITE"))
		return BG_BWHITE;
	else if(!zcmp(s,USTR "bg_CYAN"))
		return BG_BCYAN;
	else if(!zcmp(s,USTR "bg_MAGENTA"))
		return BG_BMAGENTA;
	else if(!zcmp(s,USTR "bg_BLUE"))
		return BG_BBLUE;
	else if(!zcmp(s,USTR "bg_YELLOW"))
		return BG_BYELLOW;
	else if(!zcmp(s,USTR "bg_GREEN"))
		return BG_BGREEN;
	else if(!zcmp(s,USTR "bg_RED"))
		return BG_BRED;
	else if(!zcmp(s,USTR "bg_BLACK"))
		return BG_BBLACK;

	/* Look at the "256colres.pl" PERL script in the xterm source
	   distribution to see how these work. */

	/* 256 color xterm support: bg_RGB and fg_RGB, where R, G, and B range from 0 - 5 */
	/* Codes 16 - 231 are a 6x6x6 color cube */
	else if(s[0]=='f' && s[1]=='g' && s[2]=='_' &&
		s[3]>='0' && s[3]<='5' &&
		s[4]>='0' && s[4]<='5' &&
		s[5]>='0' && s[5]<='5' && !s[6])
	        return FG_NOT_DEFAULT | ((16 + (s[3]-'0')*6*6 + (s[4]-'0')*6 + (s[5]-'0')) << FG_SHIFT);

	else if(s[0]=='b' && s[1]=='g' && s[2]=='_' &&
		  s[3]>='0' && s[3]<='5' &&
		  s[4]>='0' && s[4]<='5' &&
		  s[5]>='0' && s[5]<='5' && !s[6])
	        return BG_NOT_DEFAULT | ((16 + (s[3]-'0')*6*6 + (s[4]-'0')*6 + (s[5]-'0')) << BG_SHIFT);

	/* 256 color xterm support: shades of grey */
	/* Codes 232 - 255 are shades of grey */
	else if(s[0]=='f' && s[1]=='g' && s[2]=='_' && atoi((char *)(s+3)) >= 0 && atoi((char *)(s+3)) <= 23)
		return FG_NOT_DEFAULT | (232 + (atoi((char *)(s+3)) << FG_SHIFT));

	else if(s[0]=='b' && s[1]=='g' && s[2]=='_' && atoi((char *)(s+3)) >= 0 && atoi((char *)(s+3)) <= 23)
		return BG_NOT_DEFAULT | (232 + (atoi((char *)(s+3)) << BG_SHIFT));

	else
		return 0;
}

int meta_color(unsigned char *s)
{
	int code = 0;
	while (*s) {
		unsigned char buf[32];
		int x = 0;
		while (*s)
			if (*s && *s != '+') {
				if (x != sizeof(buf) - 1)
					buf[x++] = *s;
				++s;
			} else
				break;
		if (*s == '+')
			++s;
		buf[x] = 0;
		code |= meta_color_single(buf);
	}
	return code;
}

/* Generate a field
 *
 * 't' is SCRN to write to.
 * 'scrn' is address of field in character buffer
 * 'attr' is address of field in attribute buffer
 * 'x', 'y' are starting column and line numbers of field
 * 'ofst' is first column within string to display
 * 's', 'len' is string to generate in field
 * 'atr' is screeen attributes (and color) which should be used
 * 'width' is column width of field
 * 'flg' if set, erases to end of line
 * 'fmt' is array of attributes, one for each byte.  OK if NULL.
 */

void genfield(SCRN *t,int *scrn,int *attr,int x,int y,int ofst,unsigned char *s,int len,int atr,int width,int flg,int *fmt)
{
	int col;
	struct utf8_sm sm;
	int last_col = x + width;

	utf8_init(&sm);

	for (col = 0;len != 0 && x < last_col; len--) {
		int c = *s++;
		int wid = -1;
		int my_atr = atr;
		if (fmt) my_atr |= *fmt++;
		if (locale_map->type) {
			/* UTF-8 mode: decode character and determine its width */
			c = utf8_decode(&sm,c);
			if (c >= 0)
				wid = joe_wcwidth(1,c);
		} else {
			/* Byte mode: character is one column wide */
			wid = 1;
		}
		if (wid>=0) {
			if (col >= ofst) {
				if (x + wid > last_col /*&& (c < 128 || !unictrl(c))*/) {
					/* Character crosses end of field, so fill balance of field with '>' characters instead */
					while (x < last_col) {
						outatr(locale_map, t, scrn, attr, x, y, '>', UNDERLINE^my_atr);
						++scrn;
						++attr;
						++x;
					}
				} else if(wid) {
					/* Emit character */
					/* TODO(pts): Tell outatr where to stop at a partially written unictrl(c). */
					outatr(locale_map, t, scrn, attr, x, y, c, my_atr);
					x += wid;
					scrn += wid;
					attr += wid;
				}
			} else if ((col + wid) > ofst) {
				/* Wide character crosses left side of field */
				wid -= ofst - col;
				col = ofst;
				while (wid) {
					outatr(locale_map, t, scrn, attr, x, y, '<', my_atr);
					++scrn;
					++attr;
					++x;
					++col;
					--wid;
				}
			} else
				col += wid;
		}
	}
	/* Fill balance of field with spaces */
	while (x < last_col) {
		outatr(locale_map, t, scrn, attr, x, y, ' ', atr);
		++x;
		++scrn;
		++attr;
	}
	/* Erase to end of line */
	if (flg)
		eraeol(t, x, y, atr);
}

/* Width function for above */

int txtwidth(unsigned char *s,int len)
{
	if (locale_map->type) {
		int col=0;
		struct utf8_sm sm;
		utf8_init(&sm);

		while(len--) {
			int d = utf8_decode(&sm,*s++);
			if (d >= 0)
				col += joe_wcwidth(1,d);
		}

		return col;
	} else
		return len;
}

int txtwidth1(struct charmap *map,int tabwidth,unsigned char *s,int len)
{
	if (map->type) {
		int col=0;
		struct utf8_sm sm;
		utf8_init(&sm);

		while(len--) {
			int d = utf8_decode(&sm,*s++);
			if (d == '\t') {
				++col;
				col += tabwidth - (col % tabwidth);
			} else if (d >= 0)
				col += joe_wcwidth(1,d);
		}

		return col;
	} else {
		int col = 0;
		while (len--) {
			if (*s++ == '\t') {
				++col;
				col += tabwidth - (col % tabwidth);
			} else
				++col;
		}
		return col;
	}
}

/* Generate text with formatting escape sequences */

void genfmt(SCRN *t, int x, int y, int ofst, unsigned char *s, int atr, int flg)
{
	int *scrn = t->scrn + y * t->co + x;
	int *attr = t->attr + y * t->co + x;
	int col = 0;
	int c;
	struct utf8_sm sm;

	utf8_init(&sm);

	while ((c = *s++) != '\0')
		if (c == '\\') {
			switch (c = *s++) {
			case 'u':
			case 'U':
				atr ^= UNDERLINE;
				break;
			case 'i':
			case 'I':
				atr ^= INVERSE;
				break;
			case 'b':
			case 'B':
				atr ^= BOLD;
				break;
			case 'd':
			case 'D':
				atr ^= DIM;
				break;
			case 'f':
			case 'F':
				atr ^= BLINK;
				break;
			case 0:
				--s;
				break;
			case '@':
				c = 0;
			default: {
				if (col++ >= ofst) {
					outatr(locale_map, t, scrn, attr, x, y, (c&0x7F), atr);
					++scrn;
					++attr;
					++x;
					}
				break;
				}
			}
		} else {
			int wid = -1;
			if (locale_map->type) {
				/* UTF-8 mode: decode character and determine its width */
				c = utf8_decode(&sm,c);
				if (c >= 0) {
						wid = joe_wcwidth(1,c);
				}
			} else {
				/* Byte mode: character is one column wide */
				wid = 1;
			}

			if (wid>=0) {
				if (col >= ofst) {
					outatr(locale_map, t, scrn, attr, x, y, c, atr);
					scrn += wid;
					attr += wid;
					x += wid;
					col += wid;
				} else if (col+wid>ofst) {
					while (col<ofst) {
						++col;
						--wid;
					}
					while (wid) {
						outatr(locale_map, t, scrn, attr, x, y, '<', atr);
						++scrn;
						++attr;
						++x;
						++col;
						--wid;
					}
				} else
					col += wid;
			}
		}
	if (flg)
		eraeol(t, x, y, atr);
}

/* Determine column width of string with format codes */

int fmtlen(unsigned char *s)
{
	int col = 0;
	struct utf8_sm sm;
	int c;

	utf8_init(&sm);

	while ((c= *s++)) {
		if (c == '\\') {
			switch (*s++) {
			case 'u':
			case 'i':
			case 'd':
			case 'f':
			case 'b':
			case 'U':
			case 'I':
			case 'D':
			case 'F':
			case 'B':
				continue;
			case 0:
				return col;
			default:
				++col;
				continue;
			}
		} else {
			int wid = 0;
			if(locale_map->type) {
				c = utf8_decode(&sm,c);
				if (c>=0)
					wid = joe_wcwidth(1,c);
			} else {
				wid = 1;
			}
			col += wid;
		}
	}
	return col;
}

/* Return offset within format string which corresponds to a particular
   column */

/* FIXME: this is not valid if we land in the middle of a double-wide character */

int fmtpos(unsigned char *s, int goal)
{
	unsigned char *org = s;
	int col = 0;
	int c;
	struct utf8_sm sm;

	utf8_init(&sm);

	while ((c= *s) && col<goal) {
		s++;
		if (c == '\\') {
			switch (*s++) {
			case 'u':
			case 'i':
			case 'd':
			case 'f':
			case 'b':
			case 'U':
			case 'I':
			case 'D':
			case 'F':
			case 'B':
				continue;
			case 0:
				--s;
				break;
			default:
				++col;
				continue;
			}
		} else {
			int wid = 0;
			if(locale_map->type) {
				c = utf8_decode(&sm,c);
				if (c>=0)
					wid = joe_wcwidth(1,c);
			} else {
				wid = 1;
			}
			col += wid;
		}
	}

	return s - org + goal - col;
}
