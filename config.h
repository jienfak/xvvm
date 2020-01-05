/* See LICENSE file for copyright and license details. */

/* Jien's config. */
/* Appearance. */
static const unsigned int borderpx  = 1 ; /* Border pixel of windows. */
static const unsigned int snap = 10 ; /* Snap pixel. */
static const int showbar = 1;  /* 0 means no bar.  */
static const int topbar = 1; /* 0 means bottom bar. */
static const char *fonts[]  = { "Consolas:size=10" } ;
static const char dmenufont[] = "monospace:size=10" ;
static const char col_gray1[] = "#222222" ;
static const char col_gray2[]  = "#333333" ;
static const char col_gray3[] = "#bbbbbb" ;
static const char col_gray4[] = "#eeeeee" ;
static const char col_gray[] = "#888888" ;
static const char col_cyan[] = "#005577" ;
static const char col_red2[] = "#FF0000" ;
static const char col_red1[] = "#880000" ;
static const char col_blue[] = "#0000FF" ;
static const char col_white[] = "#FFFFFF" ;
static const char col_black[] = "#000000" ;
static const char *colors[][3] = {
	/* Foreground, background, border. */
	[SchemeNorm] = { col_black, col_white, col_gray  },
	[SchemeSel]  = { col_white, col_black,  col_white  },
} ;

/* Tagging. */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" } ;

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* Class, instance, title, tags mask, is floating, monitor */
} ;

/* Layout(s). */
static const float mfact     = 0.55 ; /* Factor of master area size [0.05..0.95]. */
static const int nmaster     = 1 ; /* Number of clients in master area. */
static const int resizehints = 1 ; /* 1 means respect size hints in tiled resizals. */

static const Layout layouts[] = {
	/* Standard is ALWAYS floating. */
	/* Symbol, arrange function. */
	[LayoutFloating] = { "[F]",      NULL }, /* No layout function means floating behavior. */
	[LayoutTile] = { "[T]",      tile }, /* Tiled layout. */
	[LayoutMonocle] = { "[M]",      monocle }, /* Maximized layout. */
} ;

/* Key definitions. */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY, KEY, view, {.ui = 1 << TAG} }, /* Change view to this tag. */ \
	{ MODKEY|ControlMask, KEY, toggleview,     {.ui = 1 << TAG} }, /* Add this tag to current view. */\
	{ MODKEY|ShiftMask, KEY, tag, {.ui = 1 << TAG} }, /* Move current window to this tag. */\
	{ MODKEY|ControlMask|ShiftMask, KEY,  toggletag, {.ui = 1 << TAG} } /* Link current wiwond to this tag. */

static char menumon[] = "0" ;
/* Easier CMD assigning. $1 in scripts is current monitor. */
#define SHCMD(cmd) /*((const char*[])*/ { "/bin/sh", "-c", cmd, menumon, NULL }/*)*/

/* It is called on "vvm" start. */
#define XMODMAP_MERGE " [ -r \"$XMODMAP\" ] && xmodmap $XMODMAP ;"
static char *rccmd[] = SHCMD("setxkbmap $DVORAK_KEYBOARD_LAYOUT ; " \
	XMODMAP_MERGE \
	"xset r rate \"$KEYBOARD_REPEAT_DELAY\" \"$KEYBOARD_REPEAT_RATE\" ;" \
	"xrdb -merge \"$XRESOURCES\" ; " \
	"eval \"$VVM_RCCMD\" ") ;

/* Helper to spawn application in terminal. */
static char *runcmd[] = SHCMD("eval $VVM_RUN_CMD" ) ; /* Menu run. */
static char *termcmd[] = SHCMD("eval  $VVM_TERMINAL") ; /* Terminal run. */
static char *popcmd[] = SHCMD("eval  $VVM_POP_UP_MENU") ; /* Pop up menu. */
/* Keyboard layouts. */
static const char *dvorakkbdcmd[] = SHCMD("setxkbmap $DVORAK_KEYBOARD_LAYOUT ;" XMODMAP_MERGE) ;
static const char *dvpkbdcmd[] = SHCMD("setxkbmap $DVP_KEYBOARD_LAYOUT ;" XMODMAP_MERGE) ;
static const char *natkbdcmd[] = SHCMD("setxkbmap $NATIVE_KEYBOARD_LAYOUT ;" XMODMAP_MERGE) ;
static const char *qwertykbdcmd[] = SHCMD("setxkbmap $QWERTY_KEYBOARD_LAYOUT ;" XMODMAP_MERGE) ;

static Key keys[] = {
	/* Modifier, key, function, argument. */
	/* Program spawners. */
	{MODKEY|ShiftMask, XK_Return, spawn, {.v = termcmd} }, /* Terminal. */
	{MODKEY|ShiftMask, XK_r, spawn, {.v = runcmd} }, /* Run CMD. (dmenu most the time) */
	/* Clients stuff and input. (The most needed) */
	{ MODKEY, XK_a, spawn, {.v = qwertykbdcmd} }, /* Qwerty. */
	{ MODKEY, XK_Tab,    spawn, {.v = dvorakkbdcmd} }, /* Dvorak. */
	{ MODKEY, XK_BackSpace, spawn, {.v = natkbdcmd} }, /* Alternative. */
	{ MODKEY, XK_Return, spawn, {.v = dvpkbdcmd} }, /* Dvorak programmer. */
	{ MODKEY, XK_x, killclient, {0} }, /* Close current window. */
	{ MODKEY,  XK_b, togglebar, {0} }, /* Toggle bar with tags and other. */
	{ MODKEY, XK_j, focusstack, {.i = +1 } }, /* Change focus via keyboard(Next). */
	{ MODKEY, XK_k, focusstack, {.i = -1 } }, /* Change focus via keyboard(Previous). */
	{ MODKEY, XK_i, incnmaster, {.i = +1 } }, /* Increase size of window table stack. */
	{ MODKEY,  XK_d, incnmaster, {.i = -1 } }, /* Decrease size of window table stack. */
	{ MODKEY, XK_h, setmfact, {.f = -0.05} }, /* Decrease master window size. */
	{ MODKEY, XK_l, setmfact, {.f = +0.05} }, /* Increase master window size. */
	{ MODKEY, XK_r, zoom, {0} }, /* Current choosen window master. */
	{ MODKEY, XK_t, setlayout, {.v = &layouts[LayoutTile]} }, /* Tile layout. */
	{ MODKEY, XK_f, setlayout, {.v = &layouts[LayoutFloating]} }, /* Floating layout. */
	{ MODKEY, XK_m, setlayout, {.v = &layouts[LayoutMonocle]} }, /* Maximized layout. */
	{ MODKEY|ShiftMask, XK_space,  setlayout, {0} },  /* Toggle layout. */
	{ MODKEY, XK_space,  togglefloating, {0} },  /* Change between floated and unfloated statement. */
	{ MODKEY, XK_0, view, {.ui = ~0 } },  /* Toggle all tags. */
	{ MODKEY|ShiftMask, XK_0, tag,  {.ui = ~0 } }, /* Move window to the next tag. */
	/* Monitor things. */
	{ MODKEY, XK_comma,  focusmon, {.i = -1 } },
	{ MODKEY, XK_period, focusmon, {.i = +1 } },
	{ MODKEY|ShiftMask, XK_comma,  tagmon, {.i = -1 } },
	{ MODKEY|ShiftMask, XK_period, tagmon, {.i = +1 } },
	/* Tags. */
	TAGKEYS(XK_1, 0),
	TAGKEYS(XK_2, 1),
	TAGKEYS(XK_3, 2),
	TAGKEYS(XK_4, 3),
	TAGKEYS(XK_5, 4),
	TAGKEYS(XK_6, 5),
	TAGKEYS(XK_7, 6),
	TAGKEYS(XK_8, 7),
	TAGKEYS(XK_9, 8),
	/* DWM hotkeys(It's rarely used, so it takes the most effort to use). */
	{ MODKEY,           XK_Escape,      quit,           {0} },              /* Quit dwm. */
} ;
/* Button definitions. */
/* Click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin. */
static Button buttons[] = {
	/* Click, event mask, button, function, argument. */
	/* Layouts. */
	{ ClkLtSymbol, 0, Button1, setlayout, {0}}, /* Toggle layout. */
	{ ClkLtSymbol, 0, Button3, setlayout,  {.v = &layouts[LayoutFloating]}}, /* Main layout. */
	{ ClkLtSymbol, 0, Button4, nextlayout,  {.i = -1}}, /* Changing layouts by mouse wheel. */
	{ ClkLtSymbol, 0, Button5, nextlayout,  {.i = +1}},
	/* Master window. */
	{ ClkStatusText, 0, Button1, setmfact, {.f = -0.05} } ,/* Decrease master window size. */
	{ ClkStatusText, 0, Button5, setmfact, {.f = -0.01} },
	{ ClkStatusText, 0, Button3,setmfact, {.f = +0.05} } , /* Increase master window size. */
	{ ClkStatusText, 0, Button4, setmfact, {.f = +0.01} },
	/* Scrolling desktop. */
	{ ClkStatusText, 0, Button1, scrolldeskhorizontal, {.i = +300} },
	{ ClkStatusText, 0, Button3, scrolldeskhorizontal, {.i = -300} },
	{ ClkStatusText, 0, Button5, scrolldeskvertical, {.i = -100} },
	{ ClkStatusText, 0, Button4, scrolldeskvertical, {.i = +100} },
	{ ClkRootWin, MODKEY|ShiftMask, Button4, scrolldeskhorizontal, {.i = +100} },
	{ ClkRootWin, MODKEY|ShiftMask, Button5, scrolldeskhorizontal, {.i = -100} },
	{ ClkRootWin, MODKEY|ControlMask, Button5, scrolldeskvertical, {.i = -100} },
	{ ClkRootWin, MODKEY|ControlMask, Button4, scrolldeskvertical, {.i = +100} },
	{ ClkClientWin, MODKEY|ShiftMask, Button4, scrolldeskhorizontal, {.i = +100} },
	{ ClkClientWin, MODKEY|ShiftMask, Button5, scrolldeskhorizontal, {.i = -100} },
	{ ClkClientWin, MODKEY|ControlMask, Button5, scrolldeskvertical, {.i = -100} },
	{ ClkClientWin, MODKEY|ControlMask, Button4, scrolldeskvertical, {.i = +100} },
	/* Calling terminal. */
	{ ClkRootWin, 0, Button2, spawn, {.v = termcmd } },
	/* Calling pop up menu. */
	{ ClkRootWin, 0, Button3, spawn, {.v = popcmd } },	
	/* Moving window by mouse. */
	{ ClkClientWin, MODKEY, Button1, movemouse, {0} },
	/* Close current window. */
	{ ClkClientWin, MODKEY|ShiftMask, Button2, killclient, {0}  },
	/* Focus on window under cursor. */
	{ ClkClientWin, MODKEY, Button2, focuscurwin, {0} },
	/* Up window on the stack of view. */
	{ ClkClientWin, MODKEY, Button4, raiseclient, {0} },
	/* Low window on the stack of view. */
	{ ClkClientWin, MODKEY, Button5, lowerclient, {0} },
	/* Resizing by mouse. */
	{ ClkClientWin, MODKEY, Button3, resizemouse, {0} },
	/* In tiled mode choose current window as master. */
	{ ClkClientWin, MODKEY|ControlMask, Button2, zoom, {0} },
	{ ClkRootWin, 0, Button1, togglebar, {0} },
	/* Tags. */
	{ ClkTagBar, 0, Button1, view, {0} },
	{ ClkTagBar, 0, Button3, toggleview, {0} },
	{ ClkTagBar, MODKEY, Button1, tag, {0} },
	{ ClkTagBar, MODKEY, Button3, toggletag, {0} },
} ;

/* Behaviour. */
static char autoraise = (char)0 ;
