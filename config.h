/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* Border pixel of windows. */
static const unsigned int snap      = 32;       /* Snap pixel.              */
static const int showbar            = 1;        /* 0 means no bar.          */
static const int topbar             = 1;        /* 0 means bottom bar.      */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#333333";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_red2[]        = "#FF0000";
static const char col_red1[]        = "#880000";
static const char col_blue[]        = "#0000FF";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_cyan  },
	[SchemeSel]  = { col_gray4, col_red1,  col_red2  },
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
	{ "Firefox",  NULL,       NULL,       0,            0,           -1 },
	{ "mpv",      NULL,       NULL,       0b111111111,  1,           -1 },
	{ "Ardour",   NULL,       NULL,       0,            1,           -1 },
	{ "ZynAddSubFX",
	              NULL,       NULL,       0,            1,           -1 },
	{ "LMMS",     NULL,       NULL,       0,            1,           -1 },
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

/* Easier CMD assigning. */
#define SHCMD(cmd) /*((const char*[])*/ { "/bin/sh", "-c", cmd, NULL }/*)*/
/* Helper to spawn application in terminal. */

/* Commands. */
static char dmenumon[2] = "0"; /* Component of dmenucmd, manipulated in spawn(). */
static char * dmenucmd[] = { "dmenu_run", "-p", "&", "-m", dmenumon, NULL }; /* DMenu. */
/*Terminal. */
static const char *termcmd[]  = SHCMD("st -e tmux new-session");
/* Tabbed terminal. */
static const char *tabtermcmd[] = SHCMD("tabbed -c st -w");
/* File manager. */
static const char *fmcmd[] = SHCMD("st -e tmux new-session lf"); 
/* Music player. */
static const char *mpcmd[] = SHCMD("st -e tmux new-session -A -s 'Music player' 'cmus'") ; 
/* Image viewer. */
static const char *imgcmd[] = SHCMD("cd \"$(xdg-user-dir PICTURES)\" ; vimiv");
/* Toggle dvorak layout.*/
static const char *kblcmd[]= SHCMD("if setxkbmap -print | grep dvorak ; then\n"
                                              "setxkbmap -layout us,ru  -option grp:alt_space_toggle\n"
                                          "else\n"
                                              "setxkbmap -layout us,ru -variant dvorak, -option grp:alt_space_toggle\n"
                                          "fi\n"
                                   "xmodmap $HOME/.Xmodmap");
/* Internet browser. */
static const char *ibcmd[] = SHCMD("jsurf");
/* Network control. */
static const char *nctlcmd[] = SHCMD("st -e tmux new-session -A -s 'Network control' 'wicd-curses'");
/* Editor. */
static const char *edcmd[] = SHCMD("st -e sh -c 'eval $EDITOR'");
/* Sound mixer. */
static const char *sndcmd[] = SHCMD("st -e tmux new-session -A -s 'Sound control' 'alsamixer'");
/* Hardware info. */
static const char *hwcmd[] = {"hardinfo", NULL};
/* IRC chat program. */
static const char *irccmd[] = SHCMD("st -e tmux new-session -A -s 'Chat' 'weechat'");
/* Execute program inside of st. */
static const char *estcmd[] = {"sh", "-c", "st -e sh -c \"eval \\\"$(dmenu_path|dmenu -p '!' -m $0)\\\"\"", dmenumon, NULL};
/* Lock the screen. */
static const char *lockcmd[] = SHCMD("slock");
/* Path type cmd. */
static const char *dmfilecmd[] = SHCMD("xdotool type \"$(dmenu_file)\"");
/* Dictionary typing. */
static const char *dictcmd[] = SHCMD("xdotool type \"$(dmenu -p 'w:' <$HOME/.dict/en_words_alpha.txt)\"");
/* Phrases access. */
static const char *phrcmd[] = SHCMD("touch $HOME/.phrases;var=`dmenu -p p: <$HOME/.phrases`; {echo \"$var\"; cat ~/.phrases} | uniq -u >>$HOME/.phrases; xdotool type \"$var\"");
/* DAW. */
static const char *dawcmd[] = {"non-session-manager", NULL};
/* Jack control. */
static const char *jackcmd[] = {"cadence", NULL};
/* Video editor. */
static const char *vecmd[] = SHCMD("st -e sudo sh -c 'nohup cin &'");
/* Graphics editor. */
static const char *gedcmd[] = {"gimp", NULL};
/* E-mail client. */
static const char *emailcmd[] = SHCMD("st -e tmux new-session -A -s 'E-mail manager' 'mutt'");
/* OS status. */
static const char *oscmd[] = SHCMD("st -e tmux new-session -A -s 'Sys. stats' 'htop'");
/* Off the machine. */
static const char *offcmd[] = {"shutdown", "--poweroff", "now", NULL};
/* Reboot the machine. */
static const char *rebootcmd[] = {"shutdown", "--reboot", "now", NULL};
/* Help. */
static const char *helpcmd[] = {"st", "-e", "man", "jdwm", NULL};


static Key keys[] = {
	/* Modifier                     Key        Function        Argument */
	/* Program spawners. */
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = dawcmd} },    /* DAW. */
	{ MODKEY|ShiftMask,             XK_j,      spawn,          {.v = jackcmd } },  /* Jack control. */
	{ MODKEY|ShiftMask,             XK_v,      spawn,          {.v = vecmd } },    /* Video editor. */
	{ MODKEY|ShiftMask,             XK_g,      spawn,          {.v = gedcmd} },    /* Graphics editor. */
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = dmenucmd } }, /* Untouched execute. */
	{ MODKEY|ShiftMask,             XK_r,      spawn,          {.v = estcmd } },   /* Terminal execute. */
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },  /* Terminal(with tmux).     */
	{ MODKEY|ShiftMask,             XK_t,      spawn,          {.v = tabtermcmd} },/* Tabbed terminal. */ 
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = fmcmd} },     /* File manager. */
	{ MODKEY|ShiftMask,             XK_m,      spawn,          {.v = mpcmd} },     /* Music player. */
	{ MODKEY|ShiftMask,             XK_b,      spawn,          {.v = ibcmd} },     /* Browser. */
	{ MODKEY|ShiftMask,             XK_i,      spawn,          {.v = imgcmd} },    /* Image viewer. */
	{ MODKEY|ShiftMask,             XK_n,      spawn,          {.v = nctlcmd} },   /* Network control. */
	{ MODKEY|ShiftMask,             XK_e,      spawn,          {.v = edcmd} },     /* Editor. */
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = sndcmd} },    /* Sound mixer. */
	{ MODKEY|ShiftMask,             XK_h,      spawn,          {.v = hwcmd }},     /* Hardware info. */
	{ MODKEY|ShiftMask,             XK_c,      spawn,          {.v = irccmd }},    /* IRC chat program. */
	{ MODKEY|ShiftMask,             XK_l,      spawn,          {.v = emailcmd }},  /* E-mail client. */
	{ MODKEY|ShiftMask,             XK_o,      spawn,          {.v = oscmd }},     /* OS stats. */

	/* Other. */

	/* Windows stuff and input(The most needed). */

	{ MODKEY,                       XK_e,      spawn,          {.v = phrcmd }},      /* Oftenly used phrases to type. */
	{ MODKEY,                       XK_slash,  spawn,          {.v = dmfilecmd }},   /* Comfortable path input with dmenu . */
	{ MODKEY,                       XK_w,      spawn,          {.v = dictcmd}},      /* Type word from the dictionary. */
	{ MODKEY,                       XK_a,      spawn,          {.v = kblcmd} },      /* Toggle dvorak. */
	{ MODKEY,                       XK_c,      killclient,     {0} },                /* Close current window. */
	{ MODKEY,                       XK_b,      togglebar,      {0} },                /* Toggle bar with tags and other. */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },         /* Change focus via keyboard(Next). */
	/*{ MODKEY,                       XK_j,      spawn,          {.v = mousemvcmd} },*/
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },         /* Change focus via keyboard(Previous). */
	/*{ MODKEY,                       XK_k,      spawn,          {.v = mousemvcmd} }, */
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },         /* Increase size of window table stack. */
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },         /* Decrease size of window table stack. */
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} } ,      /* Decrease master window size. */
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} } ,      /* Increase master window size. */
	{ MODKEY,                       XK_Return, zoom,           {0} },                /* Current choosen window master. */
	{ MODKEY,                       XK_Tab,    view,           {0} },                /* Change current choosen window to master. */
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, /* Tabbed layout.    */
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} }, /* Floating layout.  */
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} }, /* Maximized layout. */
	{ MODKEY|ShiftMask,             XK_space,  setlayout,      {0} },                /* Toggle layout. */
	{ MODKEY,                       XK_space,  togglefloating, {0} },                /* Change between floated and unfloated statement. */
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },        /* Toggle all tags. */
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },        /* Move window to the next tag. */
	/* Monitor things. */
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
	/* DWM hotkeys(It's rarely used, so it takes the most effort to use). */
	{ MODKEY|ShiftMask|ControlMask,           XK_h,      spawn,          {.v = helpcmd} },    /* Get help to jdwm. */
	{ MODKEY|ShiftMask|ControlMask,           XK_l,      spawn,          {.v = lockcmd } },  /* Lock the screen. */
	{ MODKEY|ShiftMask|ControlMask,           XK_q,      quit,           {0} },              /* Quit dwm. */
	{ MODKEY|ShiftMask|ControlMask,           XK_s,      spawn,          {.v = offcmd} },    /* Powefoff. */
	{ MODKEY|ShiftMask|ControlMask,           XK_r,      spawn,          {.v = rebootcmd} }, /* Reboot. */
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

