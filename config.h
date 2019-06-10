/* See LICENSE file for copyright and license details. */

/* Programs which this config needs:
 * tmux
 * cmus
 * lf
 * dmenu
 * st
 */

/* appearance */
static const unsigned int borderpx  = 1;        /* Border pixel of windows. */
static const unsigned int snap      = 32;       /* Snap pixel.              */
static const int showbar            = 1;        /* 0 means no bar.          */
static const int topbar             = 1;        /* 0 means bottom bar.      */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* Tagging. */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* Class      Instance    Title       Tags mask     Is floating  Monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* Layout(s). */
static const float mfact     = 0.55; /* Factor of master area size [0.05..0.95]. */
static const int nmaster     = 1;    /* Number of clients in master area. */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals. */

static const Layout layouts[] = {
	/* Symbol     Arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* Key definitions. */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, /* Change view to this tag. */ \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, /* Add this tag to current view. */\
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, /* Move current window to this tag. */\
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, /* Link current wiwond to this tag. */

/* Helper for spawning shell commands in the pre dwm-5.0 fashion. */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* Commands. */
static char dmenumon[2] = "0"; /* Component of dmenucmd, manipulated in spawn(). */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL }; /* DMenu. */
static const char *termcmd[]  = { "st", "-e", "tmux", "new-session", NULL };    /*Terminal. */
static const char *fmcmd[] = {"st", "-e", "tmux", "new-session",  "lf", NULL }; /* File manager. */
static const char *mpcmd[] = {"st", "-e", "tmux", "new-session", "cmus", NULL}; /* Music player. */
static const char *kblcmd[]= {"sh", "-c", "if setxkbmap -print | grep dvorak ; then\n" /* Toggle dvorak layout.*/
                                              "setxkbmap -layout us,ru -option grp:caps_toggle\n"
                                          "else\n"
                                              "setxkbmap -layout us,ru -variant dvorak, -option grp:caps_toggle\n"
                                          "fi", NULL};
static const char *ibcmd[] = {"jsurf", NULL}; /* Internet Browser. */

static Key keys[] = {
	/* Modifier                     Key        Function        Argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } }, /* Spawn menu to launch program. */
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },  /* Spawn terminal.     */
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = fmcmd } },     /* Spawn file manager. */
	{ MODKEY|ShiftMask,             XK_m,      spawn,          {.v = mpcmd} },     /* Spawn music player. */
	{ MODKEY|ShiftMask,             XK_b,      spawn,          {.v = ibcmd} },
	{ MODKEY,                       XK_a,      spawn,          {.v = kblcmd} },    /* Toggle dvorak. */
	{ MODKEY,                       XK_b,      togglebar,      {0} },              /* Toggle bar with tags and other. */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },       /* Change focus via keyboard(Next). */
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },       /* Change focus via keyboard(Previous). */
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },       /* Increase size of window table stack. */
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },       /* Decrease size of window table stack. */
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },     /* Decrease master window size. */
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },     /* Increase master window size. */
	{ MODKEY,                       XK_Return, zoom,           {0} },              /* Current choosen window master. */
	{ MODKEY,                       XK_Tab,    view,           {0} },              /* Change current choosen window to master. */
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },              /* Close current window. */
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, /* Tabbed layout.    */
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} }, /* Floating layout.  */
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} }, /* Maximized layout. */
	{ MODKEY,                       XK_space,  setlayout,      {0} },                /* Next layout. */
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },                /* Change between floated and unfloated statement. */
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } }, /* Toggle all tags. */
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } }, /* */
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* Button definitions. */
/* Click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin. */
static Button buttons[] = {
	/* Click                Event mask      Button          Function        Argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

