/* See "license" file for copyright and license details. */
/* Jien's config. */
/* For work requires "rc". (Can be taken from "plan9port") */

/* Appearance. */
static const unsigned int borderpx  = 1 ; /* Border pixel of windows. */
static const unsigned int snap = 10 ; /* Snap pixel. */
static const int showbar = 1;  /* 0 means no bar.  */
static const int topbar = 1; /* 0 means bottom bar. */
static const char *fonts[]  = { "Consolas:size=10" } ;
static const char col_gray[] = "#888888" ;
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


/* Tag which you start with. */
static const unsigned int tagview = 1 ;

/* Layouts on the tags you get when start WM. */
static const SetupLayout setup_layouts[9] = {
	/* Layout, mfact, nmaster. */
	{LayoutFloating,  0.55, 1}, /* 1. */
	{LayoutFloating,  0.55, 1} , /* 2. */
	{LayoutFloating,  0.55, 1}, /* 3. */
	{LayoutFloating,  0.55, 1}, /* 4. */
	{LayoutFloating,  0.55, 1}, /* 5. */
	{LayoutFloating,  0.55, 1}, /* 6. */
	{LayoutFloating,  0.55, 1}, /* 7. */
	{LayoutFloating,  0.55, 1}, /* 8. */
	{LayoutFloating,  0.55, 1}, /* 9. */
} ;

static const Layout layouts[] = {
	/* Standard is ALWAYS floating. */
	/* Symbol, arrange function. */
	[LayoutFloating] = { "[F]", NULL }, /* No layout function means floating behavior. */
	[LayoutTile] = { "[T]", tile }, /* Tiled layout. */
	[LayoutMonocle] = { "[M]", monocle }, /* Maximized layout. */
	[LayoutSplit] = {"[S]", split},  /* Split layout. */
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
#define SHCMD(cmd) { "/bin/env", "rc", "-l", "-c", cmd, menumon, NULL }/*)*/

#define XRESOURCES "$home/.Xresources"
#define XRESOURCES_MERGE "test -r "XRESOURCES" && xrdb -merge "XRESOURCES

#define XMODMAP "$home/.Xmodmap"
#define XMODMAP_MERGE " test -r "XMODMAP" && xmodmap "XMODMAP
/* Setting of window manager name which let you change the title in right up corner. */
#define SETWMNAME(str) "out = `{echo -n "str"} ; xsetroot -name $\"out"

/* Keyboard. */
#define SET_KB_LT "setxkbmap"

/* Native map for your language. */
#define NATIVE_KB_MAP "ru"

/* Option. */
#define KB_OPTION "grp:alt_space_toggle"

/* Dvorak. */
#define DVORAK_KB_LT "-layout us,"NATIVE_KB_MAP" -variant dvorak, -option "KB_OPTION
#define SET_DVORAK_KB_LT SET_KB_LT" "DVORAK_KB_LT

/* Programmer dvorak. */
#define DVP_KB_LT "-layout us,"NATIVE_KB_MAP" -variant dvp, -option "KB_OPTION
#define SET_DVP_KB_LT SET_KB_LT" "DVP_KB_LT

/* Qwerty. */
#define QWERTY_KB_LT"-layout us,"NATIVE_KB_MAP" -option "KB_OPTION
#define SET_QWERTY_KB_LT SET_KB_LT" "QWERTY_KB_LT

/* Native layout. */
#define NATIVE_KB_LT "-layout us,"NATIVE_KB_MAP" -variant dvp, -option "KB_OPTION
#define SET_NATIVE_KB_LT SET_KB_LT" "NATIVE_KB_LT

/* Keyboard options. */
#define KB_REPEAT_RATE "60"
#define KB_REPEAT_DELAY "300"
#define SET_KB_OPTIONS "xset r rate "KB_REPEAT_DELAY" "KB_REPEAT_RATE

/* It is called on "xvvm" start. */
static char *rccmd[] = SHCMD( SETWMNAME("Hello, `{whoami}") ";" \
	SET_DVORAK_KB_LT ";" \
	XMODMAP_MERGE ";"\
	SET_KB_OPTIONS";" \
	XRESOURCES_MERGE";" ) ;

/* Spawners. */
static char *runcmd[] = SHCMD(" eval `{echo -n | xmen -p ';' } ") ; /* Menu run. */
static char *outruncmd[] = SHCMD(SETWMNAME("`{ eval `{echo -n | xmen -p ';'} }")) ; /* Set WM name to output of command. */
static char *termcmd[] = SHCMD("xtrm") ; /* Terminal run. */
static char *termtcmd[] = SHCMD("9term rc -l") ; /* Text buffer terminal to run. */
/* Keyboard layouts. */
static const char *dvorakkbdcmd[] = SHCMD(SETWMNAME("dvorak") ";"SET_DVORAK_KB_LT ";" XMODMAP_MERGE ";" );
static const char *dvpkbdcmd[] = SHCMD(SETWMNAME("dvp") ";" SET_DVP_KB_LT ";" XMODMAP_MERGE ";" ) ;
static const char *natkbdcmd[] = SHCMD(SETWMNAME("native")";" SET_NATIVE_KB_LT ";" XMODMAP_MERGE ";" ) ;
static const char *qwertykbdcmd[] = SHCMD(SETWMNAME("qwerty")";" SET_QWERTY_KB_LT ";" XMODMAP_MERGE ";" ) ;

static Key keys[] = {
	/* Modifier, key, function, argument. */
	/* Program spawners. */
	{ MODKEY|ShiftMask, XK_Return, spawn, {.v = termcmd} }, /* Terminal. */
	{ MODKEY|ShiftMask, XK_t, spawn, {.v = termtcmd} }, /* Text buffer terminal. */
	{ MODKEY|ShiftMask, XK_r, spawn, {.v = runcmd} }, /* Run CMD. (dmenu most the time) */
	{ MODKEY|ShiftMask, XK_c, spawn, {.v = outruncmd} }, /* Run CMD and set it's output to WMname. */
	/* Clients stuff and input. (The most often used) */
	{ MODKEY, XK_a, spawn, {.v = qwertykbdcmd} }, /* Qwerty. */
	{ MODKEY, XK_Tab, spawn, {.v = dvorakkbdcmd} }, /* Dvorak. */
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

	{ MODKEY|ControlMask, XK_h, scrolldeskhorizontal, {.i = +300, .b = false} }, /* Scrolling desktop. */
	{ MODKEY|ControlMask, XK_l, scrolldeskhorizontal, {.i = -300, .b = false} },
	{ MODKEY|ControlMask, XK_k, scrolldeskvertical, {.i = +300, .b = false} },
	{ MODKEY|ControlMask, XK_j, scrolldeskvertical, {.i = -300, .b = false} },
	{ MODKEY, XK_r, zoom, {0} }, /* Current choosen window master. */
	{ MODKEY, XK_t, setlayout, {.v = &layouts[LayoutTile]} }, /* Tile layout. */
	{ MODKEY, XK_s, setlayout, {.v = &layouts[LayoutSplit]}}, /* Split layout. */
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
	{ ClkLtSymbol, 0, Button2,   togglefloating, {0} }, /* Toggle floating layout on current window. */
	/* Master window. */
	{ ClkStatusText, 0, Button1, setmfact, {.f = -0.05} } ,/* Decrease master window size. */
	{ ClkStatusText, 0, Button5, setmfact, {.f = -0.01} },
	{ ClkStatusText, 0, Button3,setmfact, {.f = +0.05} } , /* Increase master window size. */
	{ ClkStatusText, 0, Button4, setmfact, {.f = +0.01} },
	{ ClkRootWin, MODKEY|ShiftMask, Button4, setmfact, {.f = +0.01} },
	{ ClkRootWin, MODKEY|ShiftMask, Button5, setmfact, {.f = -0.01} },
	{ ClkClientWin, MODKEY|ShiftMask, Button4, setmfact, {.f = +0.01} },
	{ ClkClientWin, MODKEY|ShiftMask, Button5, setmfact, {.f = -0.01} },
	{ ClkRootWin, MODKEY|ControlMask, Button4, setmfact, {.f = +0.05} },
	{ ClkRootWin, MODKEY|ControlMask, Button5, setmfact, {.f = -0.05} },
	{ ClkClientWin, MODKEY|ControlMask, Button4, setmfact, {.f = +0.05} },
	{ ClkClientWin, MODKEY|ControlMask, Button5, setmfact, {.f = -0.05} },
	/* Scrolling desktop. */
	{ ClkStatusText, 0, Button1, scrolldeskhorizontal, {.i = +300, .b = false} },
	{ ClkStatusText, 0, Button3, scrolldeskhorizontal, {.i = -300, .b = false} },
	{ ClkStatusText, 0, Button5, scrolldeskvertical, {.i = -100, .b = false} },
	{ ClkStatusText, 0, Button4, scrolldeskvertical, {.i = +100, .b = false} },
	{ ClkRootWin, MODKEY|ShiftMask, Button4, scrolldeskhorizontal, {.i = +100, .b = false} },
	{ ClkRootWin, MODKEY|ShiftMask, Button5, scrolldeskhorizontal, {.i = -100, .b = false} },
	{ ClkRootWin, MODKEY|ControlMask, Button5, scrolldeskvertical, {.i = -100, .b = false} },
	{ ClkRootWin, MODKEY|ControlMask, Button4, scrolldeskvertical, {.i = +100, .b = false} },
	{ ClkClientWin, MODKEY|ShiftMask, Button4, scrolldeskhorizontal, {.i = +100, .b = false} },
	{ ClkClientWin, MODKEY|ShiftMask, Button5, scrolldeskhorizontal, {.i = -100, .b = false} },
	{ ClkClientWin, MODKEY|ControlMask, Button5, scrolldeskvertical, {.i = -100, .b = false} },
	{ ClkClientWin, MODKEY|ControlMask, Button4, scrolldeskvertical, {.i = +100, .b = false} },
	/* Changing focus. */
	{ ClkWinTitle, 0, Button4, focusstack, {.i = +1 } }, 
	{ ClkWinTitle, 0, Button5, focusstack, {.i = -1 } }, 
	/* Calling terminals. */
	{ ClkRootWin, 0, Button2, spawn, {.v = termcmd } },
	{ ClkStatusText, 0, Button2, spawn, {.v = termtcmd } },
	/* Moving window by mouse. */
	{ ClkClientWin, MODKEY, Button1, movemouse, {0} },
	{ ClkWinTitle, 0, Button1, moveclick, {0} },
	/* Close current window. */
	{ ClkClientWin, MODKEY|ShiftMask, Button2, killclient, {0}  },
	{ ClkWinTitle, 0, Button2, killclient, {0}  },
	/* Focus on window under cursor. */
	{ ClkClientWin, MODKEY, Button2, focuscurwin, {0} },
	/* Up window on the stack of view. */
	{ ClkClientWin, MODKEY, Button4, raisefocused, {0} },
	/* Low window on the stack of view. */
	{ ClkClientWin, MODKEY, Button5, lowerfocused, {0} },
	/* Resizing by mouse. */
	{ ClkClientWin, MODKEY, Button3, resizemouse, {0} },
	{ ClkWinTitle, 0, Button3, resizeclick, {0} },
	/* In tiled mode choose current window as master. */
	{ ClkClientWin, MODKEY|ControlMask, Button2, zoom, {0} },
	{ ClkRootWin, 0, Button1, togglebar, {0} },
	/* Tags. */
	{ ClkTagBar, 0, Button1, view, {0} },
	{ ClkTagBar, 0, Button3, toggleview, {0} },
	{ ClkTagBar, MODKEY, Button1, tag, {0} },
	{ ClkTagBar, MODKEY, Button3, toggletag, {0} },
} ;
/* Sides definition. Calls functions when touches borders of screens resizing or moving windows. */
/* Sides can be SideNo, SideRight, SideLeft, SideUp, SideDown. */
static Side sides[] = {
	{SideRight, scrolldeskhorizontal, {.i = -500, .b = true} },
	{SideLeft, scrolldeskhorizontal, {.i = +500, .b = true} },
	{SideUp, scrolldeskvertical, {.i = +500, .b = true} },
	{SideDown, scrolldeskvertical, {.i = -500, .b = true} },
} ;

