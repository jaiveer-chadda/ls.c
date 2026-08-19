/// @file icons/icons.h

#include <stddef.h> // needed for `wchar_t`

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

typedef struct {
	char *match;
	wchar_t icon;
} Icon;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define IC_FILE				L'' //  F15B  	[ • • • ]
#define IC_FILE_UNKNOW		L'󰡯' // F086F  󰡯	  [ • • • ]

#define IC_FOLDER			L'' //  E5FF  	[ • • • ]
#define IC_FOLDER_OPEN		L'' //  F115  	[ • • • ]

#define IC_ACF				L'' //  F1B6  	[ • • E ]
#define IC_AI				L'' //  E7B4  	[ • • E ]
#define IC_ARCHBTW			L'' //  F303  	[ • F • ]
#define IC_ASP				L'' //  F121  	[ • • E ]
#define IC_ATOM				L'' //  E764  	[ • F • ]
#define IC_AUDIO			L'' //  F001  	[ • • E ]
#define IC_BINARY			L'' //  EAE8  	[ • • E ]
#define IC_BLEND			L'󰂫' // F00AB  󰂫	  [ • • E ]
#define IC_BOOK				L'' //  E28B  	[ • • E ]
#define IC_BSPWM			L'' //  F355  	[ • F • ]
#define IC_BUN				L'' //  E76F  	[ • F • ]
#define IC_CACHE			L'' //  F49B  	[ • • E ]
#define IC_CAD				L'󰻫' // F0EEB  󰻫	  [ • • E ]
#define IC_CALENDAR			L'' //  EAB0  	[ • • E ]
#define IC_CLOCK			L'' //  F43A  	[ • F • ]
#define IC_CLOJURE_1		L'' //  E768  	[ • • E ]
#define IC_CLOJURE_2		L'' //  E76A  	[ • • E ]
#define IC_CMAKE			L'' //  E794  	[ • F E ]
#define IC_CODE_OF_CONDUCT	L'' //  F4AE  	[ • F • ]
#define IC_CODESPELL		L'󰓆' // F04C6  󰓆	  [ • F • ]
#define IC_COFFEE			L'' //  F0F4  	[ • • E ]
#define IC_COM				L'' //  E629  	[ • • E ]
#define IC_COMPRESSED		L'' //  F410  	[ • • E ]
#define IC_CONDA			L'' //  E715  	[ • F E ]
#define IC_CONFIG			L'󱁻' // F107B  󱁻	  [ • F E ]
#define IC_CONTACTS			L'󰉌' // F024C  󰉌	  [ D • • ]
#define IC_COW				L'󰆚' // F019A  󰆚	  [ • • E ]
#define IC_CR				L'' //  E62F  	[ • • E ]
#define IC_CSS3				L'' //  E749  	[ • • E ]
#define IC_CSV				L'' //  EEFC  	[ • • E ]
#define IC_CU				L'' //  E64B  	[ • • E ]
#define IC_DART				L'' //  E798  	[ • • E ]
#define IC_DATABASE			L'' //  F1C0  	[ • • E ]
#define IC_DEB				L'' //  E77D  	[ • • E ]
#define IC_DESKTOP			L'' //  F108  	[ D • • ]
#define IC_DESKTOP_EXT		L'' //  EBD1  	[ • • E ]
#define IC_DIFF				L'' //  F440  	[ • • E ]
#define IC_DISK_IMAGE		L'' //  E271  	[ • • E ]
#define IC_DOCKER			L'' //  E650  	[ • F E ]
#define IC_DOCUMENT			L'' //  F1C2  	[ • • E ]
#define IC_DOCUMENTS		L'󰲂' // F0C82  󰲂	  [ D • • ]
#define IC_DOWNLOAD			L'󰇚' // F01DA  󰇚	  [ • • E ]
#define IC_DOWNLOADS		L'󰉍' // F024D  󰉍	  [ D • • ]
#define IC_DRAWIO			L'' //  EBBA  	[ • • E ]
#define IC_DROPBOX			L'' //  E707  	[ • F • ]
#define IC_EARTH			L'' //  F0AC  	[ • F • ]
#define IC_EBUILD			L'' //  F30D  	[ • • E ]
#define IC_EDA_PCB			L'' //  EABE  	[ • • E ]
#define IC_EDA_SCH			L'󰭅' // F0B45  󰭅	  [ • • E ]
#define IC_EDITORCONFIG		L'' //  E652  	[ • F E ]
#define IC_EJS				L'' //  E618  	[ • • E ]
#define IC_ELM				L'' //  E62C  	[ • • E ]
#define IC_EMACS			L'' //  E632  	[ • F E ]
#define IC_EML				L'' //  F003  	[ • • E ]
#define IC_ENV				L'' //  F462  	[ • F E ]
#define IC_ERLANG			L'' //  E7B1  	[ • • E ]
#define IC_ESLINT			L'' //  E655  	[ • F • ]
#define IC_EXERCISM			L'' //  EBE5  	[ D • • ]
#define IC_FAVORITES		L'󰚝' // F069D  󰚝	  [ D • • ]
#define IC_FILE_3D			L'󰆧' // F01A7  󰆧	  [ • • E ]
#define IC_FLAKE			L'' //  F313  	[ • F E ]
#define IC_FOLDER_BUILD		L'󱧼' // F19FC  󱧼	  [ D • • ]
#define IC_FOLDER_CONFIG	L'' //  E5FC  	[ D • • ]
#define IC_FOLDER_GIT		L'' //  E5FB  	[ D • • ]
#define IC_FOLDER_GITHUB	L'' //  E5FD  	[ D • • ]
#define IC_FOLDER_HIDDEN	L'󱞞' // F179E  󱞞	  [ D • • ]
#define IC_FOLDER_KEY		L'󰢬' // F08AC  󰢬	  [ D • • ]
#define IC_FOLDER_NPM		L'' //  E5FA  	[ D • • ]
#define IC_FONT				L'' //  F031  	[ • F E ]
#define IC_FREECAD			L'' //  F336  	[ • F E ]
#define IC_GBA				L'󱎓' // F1393  󱎓	  [ • • E ]
#define IC_GCODE			L'󰫴' // F0AF4  󰫴	  [ • • E ]
#define IC_GFORM			L'' //  F298  	[ • • E ]
#define IC_GIMP				L'' //  F338  	[ • • E ]
#define IC_GIST_SECRET		L'' //  EAFA  	[ • • E ]
#define IC_GIT				L'󰊢' // F02A2  󰊢	  [ • F E ]
#define IC_GITLAB			L'' //  F296  	[ • F • ]
#define IC_GODOT			L'' //  E65F  	[ • • E ]
#define IC_GOOGLE_CLOUD		L'󱇶' // F11F6  󱇶	  [ • F • ]
#define IC_GRADLE			L'' //  E660  	[ • F E ]
#define IC_GRAPH			L'󱁉' // F1049  󱁉	  [ • • E ]
#define IC_GRAPHQL			L'' //  E662  	[ • • E ]
#define IC_GRUNT			L'' //  E611  	[ • F • ]
#define IC_GTK				L'' //  F362  	[ • • E ]
#define IC_GULP				L'' //  E610  	[ • F • ]
#define IC_HAML				L'' //  E664  	[ • • E ]
#define IC_HEROKU			L'' //  E77B  	[ • F • ]
#define IC_HEX				L'󱊧' // F12A7  󱊧	  [ • • E ]
#define IC_HOME				L'󱂵' // F10B5  󱂵	  [ D • • ]
#define IC_HOMEBREW			L'󱄖' // F1116  󱄖	  [ • F • ]
#define IC_HOOK				L'󰛢' // F06E2  󰛢	  [ • F • ]
#define IC_HTML5			L'' //  F13B  	[ • • E ]
#define IC_HYPRLAND			L'' //  F359  	[ • F • ]
#define IC_I3				L'' //  F35A  	[ • F • ]
#define IC_IMAGE			L'' //  F1C5  	[ • • E ]
#define IC_INFO				L'' //  F129  	[ • • E ]
#define IC_INTELLIJ			L'' //  E7B5  	[ • F E ]
#define IC_JENKINSFILE		L'' //  E66E  	[ • F • ]
#define IC_JL				L'' //  E624  	[ • • E ]
#define IC_JSON				L'' //  E60B  	[ • • E ]
#define IC_JWMRC			L'' //  F35B  	[ • • E ]
#define IC_KDE				L'' //  F373  	[ • F • ]
#define IC_KDENLIVE			L'' //  F33C  	[ • F E ]
#define IC_KEY				L'' //  EB11  	[ • • E ]
#define IC_KEYPASS			L'' //  F23E  	[ • • E ]
#define IC_KICAD			L'' //  F34C  	[ • F E ]
#define IC_KRITA			L'' //  F33D  	[ • F E ]
#define IC_LANG_ARDUINO		L'' //  F34B  	[ • • E ]
#define IC_LANG_ASSEMBLY	L'' //  E637  	[ • • E ]
#define IC_LANG_C			L'' //  E61E  	[ • • E ]
#define IC_LANG_CPP			L'' //  E61D  	[ • • E ]
#define IC_LANG_CSHARP		L'󰌛' // F031B  󰌛	  [ • • E ]
#define IC_LANG_D			L'' //  E7AF  	[ • • E ]
#define IC_LANG_ELIXIR		L'' //  E62D  	[ • F E ]
#define IC_LANG_FENNEL		L'' //  E6AF  	[ • F E ]
#define IC_LANG_FORTRAN		L'󱈚' // F121A  󱈚	  [ • • E ]
#define IC_LANG_FSHARP		L'' //  E7A7  	[ • • E ]
#define IC_LANG_GLEAM		L'󰦥' // F09A5  󰦥	  [ • • E ]
#define IC_LANG_GO			L'' //  E65E  	[ • F E ]
#define IC_LANG_GROOVY		L'' //  E775  	[ • • E ]
#define IC_LANG_HASKELL		L'' //  E777  	[ D • E ]
#define IC_LANG_HDL			L'󰍛' // F035B  󰍛	  [ • • E ]
#define IC_LANG_HOLYC		L'󰂢' // F00A2  󰂢	  [ • • E ]
#define IC_LANG_JAVA		L'' //  E256  	[ • • E ]
#define IC_LANG_JSCPT		L'' //  E74E  	[ • F E ]
#define IC_LANG_KOTLIN		L'' //  E634  	[ • • E ]
#define IC_LANG_LUA			L'' //  E620  	[ • • E ]
#define IC_LANG_NIM			L'' //  E677  	[ • • E ]
#define IC_LANG_OCAML		L'' //  E67A  	[ D F E ]
#define IC_LANG_PERL		L'' //  E67E  	[ • • E ]
#define IC_LANG_PHP			L'' //  E73D  	[ • F E ]
#define IC_LANG_PYTHON		L'' //  E606  	[ • F E ]
#define IC_LANG_R			L'' //  E68A  	[ • • E ]
#define IC_LANG_RBRAILS		L'' //  E73B  	[ • F E ]
#define IC_LANG_RUBY		L'' //  E739  	[ • F E ]
#define IC_LANG_RUST		L'' //  E68B  	[ • F E ]
#define IC_LANG_SASS		L'' //  E603  	[ • • E ]
#define IC_LANG_SCHEME		L'' //  E6B1  	[ • • E ]
#define IC_LANG_STYLUS		L'' //  E600  	[ • • E ]
#define IC_LANG_TEX			L'' //  E69B  	[ • • E ]
#define IC_LANG_TSCPT		L'' //  E628  	[ • F E ]
#define IC_LANG_V			L'' //  E6AC  	[ • • E ]
#define IC_LESS				L'' //  E758  	[ • • E ]
#define IC_LIBRARY			L'' //  EB9C  	[ • • E ]
#define IC_LICENSE			L'' //  F02D  	[ • F E ]
#define IC_LISP				L'󰅲' // F0172  󰅲	  [ • • E ]
#define IC_LOCK				L'' //  F023  	[ • F E ]
#define IC_LOG				L'' //  F18D  	[ • F E ]
#define IC_LXDE				L'' //  F363  	[ • F • ]
#define IC_LXQT				L'' //  F364  	[ • F • ]
#define IC_MAGNET			L'' //  F076  	[ • • E ]
#define IC_MAIL				L'󰇰' // F01F0  󰇰	  [ D • • ]
#define IC_MAKE				L'' //  E673  	[ • F E ]
#define IC_MARKDOWN			L'' //  F48A  	[ • • E ]
#define IC_MID				L'󰣲' // F08F2  󰣲	  [ • • E ]
#define IC_MOVIES			L'󰿎' // F0FCE  󰿎	  [ D • • ]
#define IC_MPV				L'' //  F36E  	[ • F • ]
#define IC_MSF				L'' //  F370  	[ • • E ]
#define IC_MUSIC			L'󱍙' // F1359  󱍙	  [ D • • ]
#define IC_MUSTACHE			L'' //  E60F  	[ • • E ]
#define IC_NANO				L'' //  E838  	[ • F • ]
#define IC_NEWS				L'' //  F1EA  	[ • F • ]
#define IC_NINJA			L'󰝴' // F0774  󰝴	  [ • • E ]
#define IC_NODEJS			L'' //  E718  	[ • F E ]
#define IC_NORG				L'' //  E847  	[ • • E ]
#define IC_NOTEBOOK			L'' //  E678  	[ • • E ]
#define IC_NPM				L'' //  E71E  	[ • F • ]
#define IC_NUXT				L'󱄆' // F1106  󱄆	  [ • F • ]
#define IC_ODF				L'' //  F37B  	[ • • E ]
#define IC_ODG				L'' //  F379  	[ • • E ]
#define IC_ODP				L'' //  F37A  	[ • • E ]
#define IC_ODS				L'' //  F378  	[ • • E ]
#define IC_ODT				L'' //  F37C  	[ • • E ]
#define IC_OPAM				L'󰘧' // F0627  󰘧	  [ • • E ]
#define IC_ORG				L'' //  E633  	[ • • E ]
#define IC_OS_ANDROID		L'' //  E70E  	[ • • E ]
#define IC_OS_APPLE			L'' //  F179  	[ • F E ]
#define IC_OS_LINUX			L'' //  F17C  	[ • • E ]
#define IC_OS_WINDOWS		L'' //  F17A  	[ • • E ]
#define IC_OS_WINDOWS_CMD	L'' //  EBC4  	[ • • E ]
#define IC_OUT				L'' //  EB2C  	[ • • E ]
#define IC_PAINTBRUSH		L'' //  EE72  	[ • F • ]
#define IC_PDF				L'' //  F1C1  	[ • • E ]
#define IC_PEOPLE			L'' //  EDCA  	[ • F • ]
#define IC_PHOTOSHOP		L'' //  E7B8  	[ • • E ]
#define IC_PICTURES			L'󰉏' // F024F  󰉏	  [ D • • ]
#define IC_PKG				L'' //  EB29  	[ • • E ]
#define IC_PLATFORMIO		L'' //  E682  	[ • F • ]
#define IC_PLAYLIST			L'󰲹' // F0CB9  󰲹	  [ • • E ]
#define IC_POM				L'' //  E674  	[ • F • ]
#define IC_POWERSHELL		L'' //  EBC7  	[ • • E ]
#define IC_PP				L'' //  E631  	[ • • E ]
#define IC_PRETTIER			L'' //  E6B4  	[ • F • ]
#define IC_PRIVATE_KEY		L'󰌆' // F0306  󰌆	  [ • F • ]
#define IC_PRUSASLICER		L'' //  F351  	[ • F • ]
#define IC_PUBLIC_KEY		L'󰷖' // F0DD6  󰷖	  [ • • E ]
#define IC_PURS				L'' //  E630  	[ • • E ]
#define IC_QT				L'' //  F375  	[ • F E ]
#define IC_RAZOR			L'' //  F1FA  	[ • • E ]
#define IC_RDB				L'' //  E76D  	[ • • E ]
#define IC_REACT			L'' //  E7BA  	[ • • E ]
#define IC_README			L'󰂺' // F00BA  󰂺	  [ • F E ]
#define IC_RENOVATE			L'󰉼' // F027C  󰉼	  [ • F • ]
#define IC_ROBOT			L'󰚩' // F06A9  󰚩	  [ • F • ]
#define IC_RPM				L'' //  E7BB  	[ • • E ]
#define IC_RSS				L'' //  F09E  	[ • • E ]
#define IC_SCAD				L'' //  F34E  	[ • • E ]
#define IC_SCALA			L'' //  E737  	[ • • E ]
#define IC_SECURITY			L'󰒃' // F0483  󰒃	  [ • F • ]
#define IC_SERVICE			L'' //  EBA2  	[ • • E ]
#define IC_SHEET			L'' //  F1C3  	[ • • E ]
#define IC_SHELL			L'󱆃' // F1183  󱆃	  [ • F E ]
#define IC_SHELL_CMD		L'' //  F489  	[ • F E ]
#define IC_SHIELD_CHECK		L'󰕥' // F0565  󰕥	  [ • • E ]
#define IC_SHIELD_KEY		L'󰯄' // F0BC4  󰯄	  [ • • E ]
#define IC_SHIELD_LOCK		L'󰦝' // F099D  󰦝	  [ • • E ]
#define IC_SIGNED_FILE		L'󱧃' // F19C3  󱧃	  [ • • E ]
#define IC_SLIDE			L'' //  F1C4  	[ • • E ]
#define IC_SQ_WAVE			L'󱑻' // F147B  󱑻	  [ • • E ]
#define IC_SQLITE			L'' //  E7C4  	[ • • E ]
#define IC_SRC				L'󰣞' // F08DE  󰣞	  [ D • • ]
#define IC_SSH_LOGO			L'󰣀' // F08C0  󰣀	  [ • F • ]
#define IC_STAR				L'' //  E623  	[ • F • ]
#define IC_STOW				L'' //  EEF1  	[ • F • ]
#define IC_SUBLIME			L'' //  E7AA  	[ • • E ]
#define IC_SUBTITLE			L'󰨖' // F0A16  󰨖	  [ • • E ]
#define IC_SVELTE			L'' //  E697  	[ • • E ]
#define IC_SWIFT			L'' //  E755  	[ • • E ]
#define IC_SWITCH			L'󰟡' // F07E1  󰟡	  [ • • E ]
#define IC_TCL				L'󰛓' // F06D3  󰛓	  [ • • E ]
#define IC_TERRAFORM		L'󱁢' // F1062  󱁢	  [ • • E ]
#define IC_TEXT				L'' //  F15C  	[ • • E ]
#define IC_TMUX				L'' //  EBC8  	[ • F E ]
#define IC_TODO				L'' //  F0AE  	[ • F • ]
#define IC_TOML				L'' //  E6B2  	[ • • E ]
#define IC_TORRENT			L'' //  E275  	[ • • E ]
#define IC_TRANSLATION		L'󰗊' // F05CA  󰗊	  [ • • E ]
#define IC_TRASH			L'' //  F1F8  	[ D • • ]
#define IC_TREB_CLEF		L'󰽰' // F0F70  󰽰	  [ • • E ]
#define IC_TWIG				L'' //  E61C  	[ • • E ]
#define IC_TYPST			L'' //  F37F  	[ • • E ]
#define IC_UI				L'' //  F2D0  	[ • • E ]
#define IC_UNITY			L'' //  E721  	[ • • E ]
#define IC_VAGRANT			L'⍱' //  2371  ⍱	[ • F • ]
#define IC_VALA				L'' //  E8D1  	[ • • E ]
#define IC_VECTOR			L'󰕙' // F0559  󰕙	  [ • • E ]
#define IC_VHS				L'󰨛' // F0A1B  󰨛	  [ • • E ]
#define IC_VI				L'' //  E81E  	[ • • E ]
#define IC_VIDEOS			L'' //  F03D  	[ D • E ]
#define IC_VIM				L'' //  E7C5  	[ • F E ]
#define IC_VLC				L'󰕼' // F057C  󰕼	  [ • F • ]
#define IC_VSCODE			L'' //  E70C  	[ • • E ]
#define IC_VSIX				L'󰨞' // F0A1E  󰨞	  [ • • E ]
#define IC_VUE				L'󰡄' // F0844  󰡄	  [ • • E ]
#define IC_WEBPACK			L'󰜫' // F072B  󰜫	  [ • F • ]
#define IC_WESTON			L'' //  F367  	[ • F • ]
#define IC_WRENCH			L'' //  F0AD  	[ • F • ]
#define IC_XAML				L'󰙳' // F0673  󰙳	  [ • • E ]
#define IC_XML				L'󰗀' // F05C0  󰗀	  [ • • E ]
#define IC_XORG				L'' //  F369  	[ • F • ]
#define IC_XPI				L'' //  EAE6  	[ • • E ]
#define IC_YAML				L'' //  E8EB  	[ • • • ]
#define IC_YARN				L'' //  E6A7  	[ • F • ]
#define IC_ZIG				L'' //  E6A9  	[ • F E ]


/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/// Mapping from full filenames to directory icon. This mapping should contain
/// all the directories that have a custom icon.
const Icon DIR_ICONS[] = {
	{ ".config"			, IC_FOLDER_CONFIG	}, //  E5FC  
	{ ".exercism"		, IC_EXERCISM		}, //  EBE5  
	{ ".git"			, IC_FOLDER_GIT		}, //  E5FB  
	{ ".github"			, IC_FOLDER_GITHUB	}, //  E5FD  
	{ ".npm"			, IC_FOLDER_NPM		}, //  E5FA  
	{ ".opam"			, IC_LANG_OCAML		}, //  E67A  
	{ ".ssh"			, IC_FOLDER_KEY		}, // F08AC  󰢬
	{ ".Trash"			, IC_TRASH			}, //  F1F8  
	{ "build"			, IC_FOLDER_BUILD	}, // F19FC  󱧼
	{ "cabal"			, IC_LANG_HASKELL	}, //  E777  
	{ "config"			, IC_FOLDER_CONFIG	}, //  E5FC  
	{ "Contacts"		, IC_CONTACTS		}, // F024C  󰉌
	{ "cron.d"			, IC_FOLDER_CONFIG	}, //  E5FC  
	{ "cron.daily"		, IC_FOLDER_CONFIG	}, //  E5FC  
	{ "cron.hourly"		, IC_FOLDER_CONFIG	}, //  E5FC  
	{ "cron.minutely"	, IC_FOLDER_CONFIG	}, //  E5FC  
	{ "cron.monthly"	, IC_FOLDER_CONFIG	}, //  E5FC  
	{ "cron.weekly"		, IC_FOLDER_CONFIG	}, //  E5FC  
	{ "Desktop"			, IC_DESKTOP		}, //  F108  
	{ "Documents"		, IC_DOCUMENTS		}, // F0C82  󰲂
	{ "Downloads"		, IC_DOWNLOADS		}, // F024D  󰉍
	{ "etc"				, IC_FOLDER_CONFIG	}, //  E5FC  
	{ "Favorites"		, IC_FAVORITES		}, // F069D  󰚝
	{ "hidden"			, IC_FOLDER_HIDDEN	}, // F179E  󱞞
	{ "home"			, IC_HOME			}, // F10B5  󱂵
	{ "include"			, IC_FOLDER_CONFIG	}, //  E5FC  
	{ "Mail"			, IC_MAIL			}, // F01F0  󰇰
	{ "Movies"			, IC_MOVIES			}, // F0FCE  󰿎
	{ "Music"			, IC_MUSIC			}, // F1359  󱍙
	{ "node_modules"	, IC_FOLDER_NPM		}, //  E5FA  
	{ "npm_cache"		, IC_FOLDER_NPM		}, //  E5FA  
	{ "pacman.d"		, IC_FOLDER_CONFIG	}, //  E5FC  
	{ "pam.d"			, IC_FOLDER_KEY		}, // F08AC  󰢬
	{ "Pictures"		, IC_PICTURES		}, // F024F  󰉏
	{ "src"				, IC_SRC			}, // F08DE  󰣞
	{ "ssh"				, IC_FOLDER_KEY		}, // F08AC  󰢬
	{ "sudoers.d"		, IC_FOLDER_KEY		}, // F08AC  󰢬
	{ "Videos"			, IC_VIDEOS			}, //  F03D  
	{ "xbps.d"			, IC_FOLDER_CONFIG	}, //  E5FC  
	{ "xorg.conf.d"		, IC_FOLDER_CONFIG	}, //  E5FC  
};

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

/// Mapping from full filenames to file icon. This mapping should also contain
/// all the "dot" files that have a custom icon.
const Icon FILENAME_ICONS[] = {
	{ "._DS_Store"					, IC_OS_APPLE			}, //  F179  
	{ ".aliases"					, IC_SHELL				}, // F1183  󱆃
	{ ".atom"						, IC_ATOM				}, //  E764  
	{ ".bash_aliases"				, IC_SHELL				}, // F1183  󱆃
	{ ".bash_history"				, IC_SHELL				}, // F1183  󱆃
	{ ".bash_logout"				, IC_SHELL				}, // F1183  󱆃
	{ ".bash_profile"				, IC_SHELL				}, // F1183  󱆃
	{ ".bashrc"						, IC_SHELL				}, // F1183  󱆃
	{ ".CFUserTextEncoding"			, IC_OS_APPLE			}, //  F179  
	{ ".clang-format"				, IC_CONFIG				}, // F107B  󱁻
	{ ".clang-tidy"					, IC_CONFIG				}, // F107B  󱁻
	{ ".codespellrc"				, IC_CODESPELL			}, // F04C6  󰓆
	{ ".condarc"					, IC_CONDA				}, //  E715  
	{ ".cshrc"						, IC_SHELL				}, // F1183  󱆃
	{ ".DS_Store"					, IC_OS_APPLE			}, //  F179  
	{ ".editorconfig"				, IC_EDITORCONFIG		}, //  E652  
	{ ".emacs"						, IC_EMACS				}, //  E632  
	{ ".envrc"						, IC_ENV				}, //  F462  
	{ ".eslintignore"				, IC_ESLINT				}, //  E655  
	{ ".eslintrc.cjs"				, IC_ESLINT				}, //  E655  
	{ ".eslintrc.js"				, IC_ESLINT				}, //  E655  
	{ ".eslintrc.json"				, IC_ESLINT				}, //  E655  
	{ ".eslintrc.yaml"				, IC_ESLINT				}, //  E655  
	{ ".eslintrc.yml"				, IC_ESLINT				}, //  E655  
	{ ".fennelrc"					, IC_LANG_FENNEL		}, //  E6AF  
	{ ".gcloudignore"				, IC_GOOGLE_CLOUD		}, // F11F6  󱇶
	{ ".git-blame-ignore-revs"		, IC_GIT				}, // F02A2  󰊢
	{ ".gitattributes"				, IC_GIT				}, // F02A2  󰊢
	{ ".gitconfig"					, IC_GIT				}, // F02A2  󰊢
	{ ".gitignore"					, IC_GIT				}, // F02A2  󰊢
	{ ".gitignore_global"			, IC_GIT				}, // F02A2  󰊢
	{ ".gitlab-ci.yml"				, IC_GITLAB				}, //  F296  
	{ ".gitmodules"					, IC_GIT				}, // F02A2  󰊢
	{ ".gtkrc-2.0"					, IC_GRUNT				}, //  E611  
	{ ".gvimrc"						, IC_VIM				}, //  E7C5  
	{ ".htaccess"					, IC_CONFIG				}, // F107B  󱁻
	{ ".htpasswd"					, IC_CONFIG				}, // F107B  󱁻
	{ ".idea"						, IC_INTELLIJ			}, //  E7B5  
	{ ".ideavimrc"					, IC_VIM				}, //  E7C5  
	{ ".inputrc"					, IC_CONFIG				}, // F107B  󱁻
	{ ".kshrc"						, IC_SHELL				}, // F1183  󱆃
	{ ".login"						, IC_SHELL				}, // F1183  󱆃
	{ ".logout"						, IC_SHELL				}, // F1183  󱆃
	{ ".luacheckrc"					, IC_CONFIG				}, // F107B  󱁻
	{ ".luaurc"						, IC_CONFIG				}, // F107B  󱁻
	{ ".mailmap"					, IC_GIT				}, // F02A2  󰊢
	{ ".nanorc"						, IC_NANO				}, //  E838  
	{ ".node_repl_history"			, IC_NODEJS				}, //  E718  
	{ ".npmignore"					, IC_NPM				}, //  E71E  
	{ ".npmrc"						, IC_NPM				}, //  E71E  
	{ ".nuxtrc"						, IC_NUXT				}, // F1106  󱄆
	{ ".ocamlinit"					, IC_LANG_OCAML			}, //  E67A  
	{ ".parentlock"					, IC_LOCK				}, //  F023  
	{ ".pre-commit-config.yaml"		, IC_HOOK				}, // F06E2  󰛢
	{ ".prettierignore"				, IC_PRETTIER			}, //  E6B4  
	{ ".prettierrc"					, IC_PRETTIER			}, //  E6B4  
	{ ".prettierrc.json"			, IC_PRETTIER			}, //  E6B4  
	{ ".prettierrc.json5"			, IC_PRETTIER			}, //  E6B4  
	{ ".prettierrc.toml"			, IC_PRETTIER			}, //  E6B4  
	{ ".prettierrc.yaml"			, IC_PRETTIER			}, //  E6B4  
	{ ".prettierrc.yml"				, IC_PRETTIER			}, //  E6B4  
	{ ".profile"					, IC_SHELL				}, // F1183  󱆃
	{ ".pylintrc"					, IC_CONFIG				}, // F107B  󱁻
	{ ".python_history"				, IC_LANG_PYTHON		}, //  E606  
	{ ".rustfmt.toml"				, IC_LANG_RUST			}, //  E68B  
	{ ".rvm"						, IC_LANG_RUBY			}, //  E739  
	{ ".rvmrc"						, IC_LANG_RUBY			}, //  E739  
	{ ".SRCINFO"					, IC_ARCHBTW			}, //  F303  
	{ ".stowrc"						, IC_STOW				}, //  EEF1  
	{ ".tcshrc"						, IC_SHELL				}, // F1183  󱆃
	{ ".viminfo"					, IC_VIM				}, //  E7C5  
	{ ".vimrc"						, IC_VIM				}, //  E7C5  
	{ ".Xauthority"					, IC_XORG				}, //  F369  
	{ ".xinitrc"					, IC_XORG				}, //  F369  
	{ ".Xresources"					, IC_XORG				}, //  F369  
	{ ".xsession"					, IC_XORG				}, //  F369  
	{ ".yarnrc"						, IC_YARN				}, //  E6A7  
	{ ".zlogin"						, IC_SHELL				}, // F1183  󱆃
	{ ".zlogout"					, IC_SHELL				}, // F1183  󱆃
	{ ".zprofile"					, IC_SHELL				}, // F1183  󱆃
	{ ".zsh_history"				, IC_SHELL				}, // F1183  󱆃
	{ ".zsh_sessions"				, IC_SHELL				}, // F1183  󱆃
	{ ".zshenv"						, IC_SHELL				}, // F1183  󱆃
	{ ".zshrc"						, IC_SHELL				}, // F1183  󱆃
	{ "_gvimrc"						, IC_VIM				}, //  E7C5  
	{ "_vimrc"						, IC_VIM				}, //  E7C5  
	{ "a.out"						, IC_SHELL_CMD			}, //  F489  
	{ "authorized_keys"				, IC_SSH_LOGO			}, // F08C0  󰣀
	{ "AUTHORS"						, IC_PEOPLE				}, //  EDCA  
	{ "AUTHORS.txt"					, IC_PEOPLE				}, //  EDCA  
	{ "bashrc"						, IC_SHELL				}, // F1183  󱆃
	{ "Brewfile"					, IC_HOMEBREW			}, // F1116  󱄖
	{ "Brewfile.lock.json"			, IC_HOMEBREW			}, // F1116  󱄖
	{ "bspwmrc"						, IC_BSPWM				}, //  F355  
	{ "build.gradle.kts"			, IC_GRADLE				}, //  E660  
	{ "build.zig.zon"				, IC_ZIG				}, //  E6A9  
	{ "bun.lockb"					, IC_BUN				}, //  E76F  
	{ "cantorrc"					, IC_KDE				}, //  F373  
	{ "Cargo.lock"					, IC_LANG_RUST			}, //  E68B  
	{ "Cargo.toml"					, IC_LANG_RUST			}, //  E68B  
	{ "CHANGELOG"					, IC_NEWS				}, //  F1EA  
	{ "CHANGELOG.md"				, IC_NEWS				}, //  F1EA  
	{ "CHANGES"						, IC_NEWS				}, //  F1EA  
	{ "CHANGES.md"					, IC_NEWS				}, //  F1EA  
	{ "CMakeLists.txt"				, IC_CMAKE				}, //  E794  
	{ "CODE_OF_CONDUCT"				, IC_CODE_OF_CONDUCT	}, //  F4AE  
	{ "CODE_OF_CONDUCT.md"			, IC_CODE_OF_CONDUCT	}, //  F4AE  
	{ "COMMIT_EDITMSG"				, IC_GIT				}, // F02A2  󰊢
	{ "compose.yaml"				, IC_DOCKER				}, //  E650  
	{ "compose.yml"					, IC_DOCKER				}, //  E650  
	{ "composer.json"				, IC_LANG_PHP			}, //  E73D  
	{ "composer.lock"				, IC_LANG_PHP			}, //  E73D  
	{ "config"						, IC_CONFIG				}, // F107B  󱁻
	{ "config.ru"					, IC_LANG_RUBY			}, //  E739  
	{ "config.status"				, IC_CONFIG				}, // F107B  󱁻
	{ "configure"					, IC_WRENCH				}, //  F0AD  
	{ "configure.ac"				, IC_CONFIG				}, // F107B  󱁻
	{ "configure.in"				, IC_CONFIG				}, // F107B  󱁻
	{ "constraints.txt"				, IC_LANG_PYTHON		}, //  E606  
	{ "COPYING"						, IC_LICENSE			}, //  F02D  
	{ "COPYRIGHT"					, IC_LICENSE			}, //  F02D  
	{ "crontab"						, IC_CONFIG				}, // F107B  󱁻
	{ "crypttab"					, IC_CONFIG				}, // F107B  󱁻
	{ "csh.cshrc"					, IC_SHELL				}, // F1183  󱆃
	{ "csh.login"					, IC_SHELL				}, // F1183  󱆃
	{ "csh.logout"					, IC_SHELL				}, // F1183  󱆃
	{ "docker-compose.yaml"			, IC_DOCKER				}, //  E650  
	{ "docker-compose.yml"			, IC_DOCKER				}, //  E650  
	{ "Dockerfile"					, IC_DOCKER				}, //  E650  
	{ "dropbox"						, IC_DROPBOX			}, //  E707  
	{ "dune"						, IC_LANG_OCAML			}, //  E67A  
	{ "dune-project"				, IC_WRENCH				}, //  F0AD  
	{ "Earthfile"					, IC_EARTH				}, //  F0AC  
	{ "environment"					, IC_CONFIG				}, // F107B  󱁻
	{ "favicon.ico"					, IC_STAR				}, //  E623  
	{ "fennelrc"					, IC_LANG_FENNEL		}, //  E6AF  
	{ "flake.lock"					, IC_FLAKE				}, //  F313  
	{ "fonts.conf"					, IC_FONT				}, //  F031  
	{ "fp-info-cache"				, IC_KICAD				}, //  F34C  
	{ "fp-lib-table"				, IC_KICAD				}, //  F34C  
	{ "FreeCAD.conf"				, IC_FREECAD			}, //  F336  
	{ "Gemfile"						, IC_LANG_RUBY			}, //  E739  
	{ "Gemfile.lock"				, IC_LANG_RUBY			}, //  E739  
	{ "GNUmakefile"					, IC_MAKE				}, //  E673  
	{ "go.mod"						, IC_LANG_GO			}, //  E65E  
	{ "go.sum"						, IC_LANG_GO			}, //  E65E  
	{ "go.work"						, IC_LANG_GO			}, //  E65E  
	{ "gradle"						, IC_GRADLE				}, //  E660  
	{ "gradle.properties"			, IC_GRADLE				}, //  E660  
	{ "gradlew"						, IC_GRADLE				}, //  E660  
	{ "gradlew.bat"					, IC_GRADLE				}, //  E660  
	{ "group"						, IC_LOCK				}, //  F023  
	{ "gruntfile.coffee"			, IC_GRUNT				}, //  E611  
	{ "gruntfile.js"				, IC_GRUNT				}, //  E611  
	{ "gruntfile.ls"				, IC_GRUNT				}, //  E611  
	{ "gshadow"						, IC_LOCK				}, //  F023  
	{ "gtkrc"						, IC_GRUNT				}, //  E611  
	{ "gulpfile.coffee"				, IC_GULP				}, //  E610  
	{ "gulpfile.js"					, IC_GULP				}, //  E610  
	{ "gulpfile.ls"					, IC_GULP				}, //  E610  
	{ "heroku.yml"					, IC_HEROKU				}, //  E77B  
	{ "hostname"					, IC_CONFIG				}, // F107B  󱁻
	{ "hypridle.conf"				, IC_HYPRLAND			}, //  F359  
	{ "hyprland.conf"				, IC_HYPRLAND			}, //  F359  
	{ "hyprlock.conf"				, IC_HYPRLAND			}, //  F359  
	{ "hyprpaper.conf"				, IC_HYPRLAND			}, //  F359  
	{ "i3blocks.conf"				, IC_I3					}, //  F35A  
	{ "i3status.conf"				, IC_I3					}, //  F35A  
	{ "id_dsa"						, IC_PRIVATE_KEY		}, // F0306  󰌆
	{ "id_ecdsa"					, IC_PRIVATE_KEY		}, // F0306  󰌆
	{ "id_ecdsa_sk"					, IC_PRIVATE_KEY		}, // F0306  󰌆
	{ "id_ed25519"					, IC_PRIVATE_KEY		}, // F0306  󰌆
	{ "id_ed25519_sk"				, IC_PRIVATE_KEY		}, // F0306  󰌆
	{ "id_rsa"						, IC_PRIVATE_KEY		}, // F0306  󰌆
	{ "index.theme"					, IC_PAINTBRUSH			}, //  EE72  
	{ "inputrc"						, IC_CONFIG				}, // F107B  󱁻
	{ "Jenkinsfile"					, IC_JENKINSFILE		}, //  E66E  
	{ "jsconfig.json"				, IC_LANG_JSCPT			}, //  E74E  
	{ "Justfile"					, IC_WRENCH				}, //  F0AD  
	{ "justfile"					, IC_WRENCH				}, //  F0AD  
	{ "kalgebrarc"					, IC_KDE				}, //  F373  
	{ "kdeglobals"					, IC_KDE				}, //  F373  
	{ "kdenlive-layoutsrc"			, IC_KDENLIVE			}, //  F33C  
	{ "kdenliverc"					, IC_KDENLIVE			}, //  F33C  
	{ "known_hosts"					, IC_SSH_LOGO			}, // F08C0  󰣀
	{ "kritadisplayrc"				, IC_KRITA				}, //  F33D  
	{ "kritarc"						, IC_KRITA				}, //  F33D  
	{ "LICENCE"						, IC_LICENSE			}, //  F02D  
	{ "LICENCE.md"					, IC_LICENSE			}, //  F02D  
	{ "LICENCE.txt"					, IC_LICENSE			}, //  F02D  
	{ "LICENSE"						, IC_LICENSE			}, //  F02D  
	{ "LICENSE-APACHE"				, IC_LICENSE			}, //  F02D  
	{ "LICENSE-MIT"					, IC_LICENSE			}, //  F02D  
	{ "LICENSE.md"					, IC_LICENSE			}, //  F02D  
	{ "LICENSE.txt"					, IC_LICENSE			}, //  F02D  
	{ "localized"					, IC_OS_APPLE			}, //  F179  
	{ "localtime"					, IC_CLOCK				}, //  F43A  
	{ "lock"						, IC_LOCK				}, //  F023  
	{ "LOCK"						, IC_LOCK				}, //  F023  
	{ "log"							, IC_LOG				}, //  F18D  
	{ "LOG"							, IC_LOG				}, //  F18D  
	{ "lxde-rc.xml"					, IC_LXDE				}, //  F363  
	{ "lxqt.conf"					, IC_LXQT				}, //  F364  
	{ "Makefile"					, IC_MAKE				}, //  E673  
	{ "makefile"					, IC_MAKE				}, //  E673  
	{ "Makefile.ac"					, IC_MAKE				}, //  E673  
	{ "Makefile.am"					, IC_MAKE				}, //  E673  
	{ "Makefile.in"					, IC_MAKE				}, //  E673  
	{ "MANIFEST"					, IC_LANG_PYTHON		}, //  E606  
	{ "MANIFEST.in"					, IC_LANG_PYTHON		}, //  E606  
	{ "mix.lock"					, IC_LANG_ELIXIR		}, //  E62D  
	{ "mpv.conf"					, IC_MPV				}, //  F36E  
	{ "NEWS"						, IC_NEWS				}, //  F1EA  
	{ "NEWS.md"						, IC_NEWS				}, //  F1EA  
	{ "npm-shrinkwrap.json"			, IC_NPM				}, //  E71E  
	{ "npmrc"						, IC_NPM				}, //  E71E  
	{ "package-lock.json"			, IC_NPM				}, //  E71E  
	{ "package.json"				, IC_NPM				}, //  E71E  
	{ "passwd"						, IC_LOCK				}, //  F023  
	{ "php.ini"						, IC_LANG_PHP			}, //  E73D  
	{ "PKGBUILD"					, IC_ARCHBTW			}, //  F303  
	{ "platformio.ini"				, IC_PLATFORMIO			}, //  E682  
	{ "pom.xml"						, IC_POM				}, //  E674  
	{ "Procfile"					, IC_HEROKU				}, //  E77B  
	{ "profile"						, IC_SHELL				}, // F1183  󱆃
	{ "PrusaSlicer.ini"				, IC_PRUSASLICER		}, //  F351  
	{ "PrusaSlicerGcodeViewer.ini"	, IC_PRUSASLICER		}, //  F351  
	{ "pyproject.toml"				, IC_LANG_PYTHON		}, //  E606  
	{ "pyvenv.cfg"					, IC_LANG_PYTHON		}, //  E606  
	{ "qt5ct.conf"					, IC_QT					}, //  F375  
	{ "qt6ct.conf"					, IC_QT					}, //  F375  
	{ "QtProject.conf"				, IC_QT					}, //  F375  
	{ "Rakefile"					, IC_LANG_RUBY			}, //  E739  
	{ "README"						, IC_README				}, // F00BA  󰂺
	{ "README.md"					, IC_README				}, // F00BA  󰂺
	{ "release.toml"				, IC_LANG_RUST			}, //  E68B  
	{ "renovate.json"				, IC_RENOVATE			}, // F027C  󰉼
	{ "requirements.txt"			, IC_LANG_PYTHON		}, //  E606  
	{ "robots.txt"					, IC_ROBOT				}, // F06A9  󰚩
	{ "rubydoc"						, IC_LANG_RBRAILS		}, //  E73B  
	{ "rvmrc"						, IC_LANG_RUBY			}, //  E739  
	{ "SECURITY"					, IC_SECURITY			}, // F0483  󰒃
	{ "SECURITY.md"					, IC_SECURITY			}, // F0483  󰒃
	{ "settings.gradle.kts"			, IC_GRADLE				}, //  E660  
	{ "shadow"						, IC_LOCK				}, //  F023  
	{ "shells"						, IC_CONFIG				}, // F107B  󱁻
	{ "sudoers"						, IC_LOCK				}, //  F023  
	{ "sxhkdrc"						, IC_CONFIG				}, // F107B  󱁻
	{ "sym-lib-table"				, IC_KICAD				}, //  F34C  
	{ "timezone"					, IC_CLOCK				}, //  F43A  
	{ "tmux.conf"					, IC_TMUX				}, //  EBC8  
	{ "tmux.conf.local"				, IC_TMUX				}, //  EBC8  
	{ "TODO"						, IC_TODO				}, //  F0AE  
	{ "TODO.md"						, IC_TODO				}, //  F0AE  
	{ "tsconfig.json"				, IC_LANG_TSCPT			}, //  E628  
	{ "Vagrantfile"					, IC_VAGRANT			}, //  2371  ⍱
	{ "vlcrc"						, IC_VLC				}, // F057C  󰕼
	{ "webpack.config.js"			, IC_WEBPACK			}, // F072B  󰜫
	{ "weston.ini"					, IC_WESTON				}, //  F367  
	{ "xmobarrc"					, IC_XORG				}, //  F369  
	{ "xmobarrc.hs"					, IC_XORG				}, //  F369  
	{ "xmonad.hs"					, IC_XORG				}, //  F369  
	{ "xorg.conf"					, IC_XORG				}, //  F369  
	{ "xsettingsd.conf"				, IC_XORG				}, //  F369  
	{ "yarn.lock"					, IC_YARN				}, //  E6A7  
	{ "zlogin"						, IC_SHELL				}, // F1183  󱆃
	{ "zlogout"						, IC_SHELL				}, // F1183  󱆃
	{ "zprofile"					, IC_SHELL				}, // F1183  󱆃
	{ "zshenv"						, IC_SHELL				}, // F1183  󱆃
	{ "zshrc"						, IC_SHELL				}, // F1183  󱆃
};

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

const Icon EXT_ICONS[] = {
	{ "123dx"			, IC_CAD			}, // F0EEB  󰻫
	{ "3dm"				, IC_CAD			}, // F0EEB  󰻫
	{ "3g2"				, IC_VIDEOS			}, //  F03D  
	{ "3gp"				, IC_VIDEOS			}, //  F03D  
	{ "3gp2"			, IC_VIDEOS			}, //  F03D  
	{ "3gpp"			, IC_VIDEOS			}, //  F03D  
	{ "3gpp2"			, IC_VIDEOS			}, //  F03D  
	{ "3mf"				, IC_FILE_3D		}, // F01A7  󰆧
	{ "7z"				, IC_COMPRESSED		}, //  F410  
	{ "a"				, IC_OS_LINUX		}, //  F17C  
	{ "aac"				, IC_AUDIO			}, //  F4AE  
	{ "acf"				, IC_ACF			}, //  F1B6  
	{ "age"				, IC_SHIELD_LOCK	}, // F099D  󰦝
	{ "ai"				, IC_AI				}, //  E7B4  
	{ "aif"				, IC_AUDIO			}, //  F4AE  
	{ "aifc"			, IC_AUDIO			}, //  F4AE  
	{ "aiff"			, IC_AUDIO			}, //  F4AE  
	{ "alac"			, IC_AUDIO			}, //  F4AE  
	{ "android"			, IC_OS_ANDROID		}, //  E70E  
	{ "ape"				, IC_AUDIO			}, //  F4AE  
	{ "apk"				, IC_OS_ANDROID		}, //  E70E  
	{ "app"				, IC_BINARY			}, //  EAE8  
	{ "apple"			, IC_OS_APPLE		}, //  F179  
	{ "applescript"		, IC_OS_APPLE		}, //  F179  
	{ "ar"				, IC_COMPRESSED		}, //  F410  
	{ "arj"				, IC_COMPRESSED		}, //  F410  
	{ "arw"				, IC_IMAGE			}, //  F1C5  
	{ "asc"				, IC_SHIELD_LOCK	}, // F099D  󰦝
	{ "asm"				, IC_LANG_ASSEMBLY	}, //  E637  
	{ "asp"				, IC_ASP			}, //  F121  
	{ "ass"				, IC_SUBTITLE		}, // F0A16  󰨖
	{ "avi"				, IC_VIDEOS			}, //  F03D  
	{ "avif"			, IC_IMAGE			}, //  F1C5  
	{ "avro"			, IC_JSON			}, //  E60B  
	{ "awk"				, IC_SHELL_CMD		}, //  F489  
	{ "bash"			, IC_SHELL_CMD		}, //  F489  
	{ "bat"				, IC_OS_WINDOWS_CMD	}, //  EBC4  
	{ "bats"			, IC_SHELL_CMD		}, //  F489  
	{ "bdf"				, IC_FONT			}, //  F031  
	{ "bib"				, IC_LANG_TEX		}, //  E69B  
	{ "bin"				, IC_BINARY			}, //  EAE8  
	{ "blend"			, IC_BLEND			}, // F00AB  󰂫
	{ "bmp"				, IC_IMAGE			}, //  F1C5  
	{ "br"				, IC_COMPRESSED		}, //  F410  
	{ "brd"				, IC_EDA_PCB		}, //  EABE  
	{ "brep"			, IC_CAD			}, // F0EEB  󰻫
	{ "bst"				, IC_LANG_TEX		}, //  E69B  
	{ "bundle"			, IC_OS_APPLE		}, //  F179  
	{ "bz"				, IC_COMPRESSED		}, //  F410  
	{ "bz2"				, IC_COMPRESSED		}, //  F410  
	{ "bz3"				, IC_COMPRESSED		}, //  F410  
	{ "c"				, IC_LANG_C			}, //  E61E  
	{ "c++"				, IC_LANG_CPP		}, //  E61D  
	{ "cab"				, IC_OS_WINDOWS		}, //  F17A  
	{ "cache"			, IC_CACHE			}, //  F49B  
	{ "cast"			, IC_VIDEOS			}, //  F03D  
	{ "catpart"			, IC_CAD			}, // F0EEB  󰻫
	{ "catproduct"		, IC_CAD			}, // F0EEB  󰻫
	{ "cbr"				, IC_IMAGE			}, //  F1C5  
	{ "cbz"				, IC_IMAGE			}, //  F1C5  
	{ "cc"				, IC_LANG_CPP		}, //  E61D  
	{ "cert"			, IC_GIST_SECRET	}, //  EAFA  
	{ "cfg"				, IC_CONFIG			}, // F107B  󱁻
	{ "cjs"				, IC_LANG_JSCPT		}, //  E74E  
	{ "class"			, IC_LANG_JAVA		}, //  E256  
	{ "clj"				, IC_CLOJURE_1		}, //  E768  
	{ "cljc"			, IC_CLOJURE_1		}, //  E768  
	{ "cljs"			, IC_CLOJURE_2		}, //  E76A  
	{ "cls"				, IC_LANG_TEX		}, //  E69B  
	{ "cmake"			, IC_CMAKE			}, //  E794  
	{ "cmd"				, IC_OS_WINDOWS		}, //  F17A  
	{ "coffee"			, IC_COFFEE			}, //  F0F4  
	{ "com"				, IC_COM			}, //  E629  
	{ "conda"			, IC_CONDA			}, //  E715  
	{ "conf"			, IC_CONFIG			}, // F107B  󱁻
	{ "config"			, IC_CONFIG			}, // F107B  󱁻
	{ "cow"				, IC_COW			}, // F019A  󰆚
	{ "cp"				, IC_LANG_CPP		}, //  E61D  
	{ "cpio"			, IC_COMPRESSED		}, //  F410  
	{ "cpp"				, IC_LANG_CPP		}, //  E61D  
	{ "cr"				, IC_CR				}, //  E62F  
	{ "cr2"				, IC_IMAGE			}, //  F1C5  
	{ "crdownload"		, IC_DOWNLOAD		}, // F01DA  󰇚
	{ "crt"				, IC_GIST_SECRET	}, //  EAFA  
	{ "cs"				, IC_LANG_CSHARP	}, // F031B  󰌛
	{ "csh"				, IC_SHELL_CMD		}, //  F489  
	{ "cshtml"			, IC_RAZOR			}, //  F1FA  
	{ "csproj"			, IC_LANG_CSHARP	}, // F031B  󰌛
	{ "css"				, IC_CSS3			}, //  E749  
	{ "csv"				, IC_CSV			}, //  EEFC  
	{ "csx"				, IC_LANG_CSHARP	}, // F031B  󰌛
	{ "cts"				, IC_LANG_TSCPT		}, //  E628  
	{ "cu"				, IC_CU				}, //  E64B  
	{ "cue"				, IC_PLAYLIST		}, // F0CB9  󰲹
	{ "cxx"				, IC_LANG_CPP		}, //  E61D  
	{ "d"				, IC_LANG_D			}, //  E7AF  
	{ "dart"			, IC_DART			}, //  E798  
	{ "db"				, IC_DATABASE		}, //  F1C0  
	{ "db3"				, IC_SQLITE			}, //  E7C4  
	{ "dconf"			, IC_DATABASE		}, //  F1C0  
	{ "deb"				, IC_DEB			}, //  E77D  
	{ "desktop"			, IC_DESKTOP_EXT	}, //  EBD1  
	{ "di"				, IC_LANG_D			}, //  E7AF  
	{ "diff"			, IC_DIFF			}, //  F440  
	{ "djv"				, IC_DOCUMENT		}, //  F1C2  
	{ "djvu"			, IC_DOCUMENT		}, //  F1C2  
	{ "dll"				, IC_LIBRARY		}, //  EB9C  
	{ "dmg"				, IC_DISK_IMAGE		}, //  E271  
	{ "doc"				, IC_DOCUMENT		}, //  F1C2  
	{ "dockerfile"		, IC_DOCKER			}, //  E650  
	{ "dockerignore"	, IC_DOCKER			}, //  E650  
	{ "docm"			, IC_DOCUMENT		}, //  F1C2  
	{ "docx"			, IC_DOCUMENT		}, //  F1C2  
	{ "dot"				, IC_GRAPH			}, // F1049  󱁉
	{ "download"		, IC_DOWNLOAD		}, // F01DA  󰇚
	{ "drawio"			, IC_DRAWIO			}, //  EBBA  
	{ "dump"			, IC_DATABASE		}, //  F1C0  
	{ "dvi"				, IC_IMAGE			}, //  F1C5  
	{ "dwg"				, IC_CAD			}, // F0EEB  󰻫
	{ "dxf"				, IC_CAD			}, // F0EEB  󰻫
	{ "dylib"			, IC_OS_APPLE		}, //  F179  
	{ "ebook"			, IC_BOOK			}, //  E28B  
	{ "ebuild"			, IC_EBUILD			}, //  F30D  
	{ "editorconfig"	, IC_EDITORCONFIG	}, //  E652  
	{ "edn"				, IC_CLOJURE_2		}, //  E76A  
	{ "eex"				, IC_LANG_ELIXIR	}, //  E62D  
	{ "ejs"				, IC_EJS			}, //  E618  
	{ "el"				, IC_EMACS			}, //  E632  
	{ "elc"				, IC_EMACS			}, //  E632  
	{ "elf"				, IC_BINARY			}, //  EAE8  
	{ "elm"				, IC_ELM			}, //  E62C  
	{ "eml"				, IC_EML			}, //  F003  
	{ "env"				, IC_ENV			}, //  F462  
	{ "eot"				, IC_FONT			}, //  F031  
	{ "eps"				, IC_VECTOR			}, // F0559  󰕙
	{ "epub"			, IC_BOOK			}, //  E28B  
	{ "erb"				, IC_LANG_RBRAILS	}, //  E73B  
	{ "erl"				, IC_ERLANG			}, //  E7B1  
	{ "ex"				, IC_LANG_ELIXIR	}, //  E62D  
	{ "exe"				, IC_OS_WINDOWS_CMD	}, //  EBC4  
	{ "exs"				, IC_LANG_ELIXIR	}, //  E62D  
	{ "f"				, IC_LANG_FORTRAN	}, // F121A  󱈚
	{ "f#"				, IC_LANG_FSHARP	}, //  E7A7  
	{ "f3d"				, IC_CAD			}, // F0EEB  󰻫
	{ "f3z"				, IC_CAD			}, // F0EEB  󰻫
	{ "f90"				, IC_LANG_FORTRAN	}, // F121A  󱈚
	{ "fbx"				, IC_FILE_3D		}, // F01A7  󰆧
	{ "fcbak"			, IC_FREECAD		}, //  F336  
	{ "fcmacro"			, IC_FREECAD		}, //  F336  
	{ "fcmat"			, IC_FREECAD		}, //  F336  
	{ "fcparam"			, IC_FREECAD		}, //  F336  
	{ "fcscript"		, IC_FREECAD		}, //  F336  
	{ "fcstd"			, IC_FREECAD		}, //  F336  
	{ "fcstd1"			, IC_FREECAD		}, //  F336  
	{ "fctb"			, IC_FREECAD		}, //  F336  
	{ "fctl"			, IC_FREECAD		}, //  F336  
	{ "fdmdownload"		, IC_DOWNLOAD		}, // F01DA  󰇚
	{ "fish"			, IC_SHELL_CMD		}, //  F489  
	{ "flac"			, IC_AUDIO			}, //  F4AE  
	{ "flc"				, IC_FONT			}, //  F031  
	{ "flf"				, IC_FONT			}, //  F031  
	{ "flv"				, IC_VIDEOS			}, //  F03D  
	{ "fnl"				, IC_LANG_FENNEL	}, //  E6AF  
	{ "fnt"				, IC_FONT			}, //  F031  
	{ "fodg"			, IC_ODG			}, //  F379  
	{ "fodp"			, IC_ODP			}, //  F37A  
	{ "fods"			, IC_ODS			}, //  F378  
	{ "fodt"			, IC_ODT			}, //  F37C  
	{ "fon"				, IC_FONT			}, //  F031  
	{ "font"			, IC_FONT			}, //  F031  
	{ "for"				, IC_LANG_FORTRAN	}, // F121A  󱈚
	{ "fs"				, IC_LANG_FSHARP	}, //  E7A7  
	{ "fsi"				, IC_LANG_FSHARP	}, //  E7A7  
	{ "fsproj"			, IC_LANG_FSHARP	}, //  E7A7  
	{ "fsscript"		, IC_LANG_FSHARP	}, //  E7A7  
	{ "fsx"				, IC_LANG_FSHARP	}, //  E7A7  
	{ "gba"				, IC_GBA			}, // F1393  󱎓
	{ "gbl"				, IC_EDA_PCB		}, //  EABE  
	{ "gbo"				, IC_EDA_PCB		}, //  EABE  
	{ "gbp"				, IC_EDA_PCB		}, //  EABE  
	{ "gbr"				, IC_EDA_PCB		}, //  EABE  
	{ "gbs"				, IC_EDA_PCB		}, //  EABE  
	{ "gcode"			, IC_GCODE			}, // F0AF4  󰫴
	{ "gd"				, IC_GODOT			}, //  E65F  
	{ "gdoc"			, IC_DOCUMENT		}, //  F1C2  
	{ "gem"				, IC_LANG_RUBY		}, //  E739  
	{ "gemfile"			, IC_LANG_RUBY		}, //  E739  
	{ "gemspec"			, IC_LANG_RUBY		}, //  E739  
	{ "gform"			, IC_GFORM			}, //  F298  
	{ "gif"				, IC_IMAGE			}, //  F1C5  
	{ "git"				, IC_GIT			}, // F02A2  󰊢
	{ "gleam"			, IC_LANG_GLEAM		}, // F09A5  󰦥
	{ "gm1"				, IC_EDA_PCB		}, //  EABE  
	{ "gml"				, IC_EDA_PCB		}, //  EABE  
	{ "go"				, IC_LANG_GO		}, //  E65E  
	{ "godot"			, IC_GODOT			}, //  E65F  
	{ "gpg"				, IC_SHIELD_LOCK	}, // F099D  󰦝
	{ "gql"				, IC_GRAPHQL		}, //  E662  
	{ "gradle"			, IC_GRADLE			}, //  E660  
	{ "graphql"			, IC_GRAPHQL		}, //  E662  
	{ "gresource"		, IC_GTK			}, //  F362  
	{ "groovy"			, IC_LANG_GROOVY	}, //  E775  
	{ "gsheet"			, IC_SHEET			}, //  F1C3  
	{ "gslides"			, IC_SLIDE			}, //  F1C4  
	{ "gtl"				, IC_EDA_PCB		}, //  EABE  
	{ "gto"				, IC_EDA_PCB		}, //  EABE  
	{ "gtp"				, IC_EDA_PCB		}, //  EABE  
	{ "gts"				, IC_EDA_PCB		}, //  EABE  
	{ "guardfile"		, IC_LANG_RUBY		}, //  E739  
	{ "gv"				, IC_GRAPH			}, // F1049  󱁉
	{ "gvy"				, IC_LANG_GROOVY	}, //  E775  
	{ "gz"				, IC_COMPRESSED		}, //  F410  
	{ "h"				, IC_LANG_C			}, //  E61E  
	{ "h++"				, IC_LANG_CPP		}, //  E61D  
	{ "h264"			, IC_VIDEOS			}, //  F03D  
	{ "haml"			, IC_HAML			}, //  E664  
	{ "hbs"				, IC_MUSTACHE		}, //  E60F  
	{ "hc"				, IC_LANG_HOLYC		}, // F00A2  󰂢
	{ "heic"			, IC_IMAGE			}, //  F1C5  
	{ "heics"			, IC_VIDEOS			}, //  F03D  
	{ "heif"			, IC_IMAGE			}, //  F1C5  
	{ "hex"				, IC_HEX			}, // F12A7  󱊧
	{ "hh"				, IC_LANG_CPP		}, //  E61D  
	{ "hi"				, IC_BINARY			}, //  EAE8  
	{ "hpp"				, IC_LANG_CPP		}, //  E61D  
	{ "hrl"				, IC_ERLANG			}, //  E7B1  
	{ "hs"				, IC_LANG_HASKELL	}, //  E777  
	{ "htm"				, IC_HTML5			}, //  F13B  
	{ "html"			, IC_HTML5			}, //  F13B  
	{ "hxx"				, IC_LANG_CPP		}, //  E61D  
	{ "iam"				, IC_CAD			}, // F0EEB  󰻫
	{ "ical"			, IC_CALENDAR		}, //  EAB0  
	{ "icalendar"		, IC_CALENDAR		}, //  EAB0  
	{ "ico"				, IC_IMAGE			}, //  F1C5  
	{ "ics"				, IC_CALENDAR		}, //  EAB0  
	{ "ifb"				, IC_CALENDAR		}, //  EAB0  
	{ "ifc"				, IC_CAD			}, // F0EEB  󰻫
	{ "ige"				, IC_CAD			}, // F0EEB  󰻫
	{ "iges"			, IC_CAD			}, // F0EEB  󰻫
	{ "igs"				, IC_CAD			}, // F0EEB  󰻫
	{ "image"			, IC_DISK_IMAGE		}, //  E271  
	{ "img"				, IC_DISK_IMAGE		}, //  E271  
	{ "iml"				, IC_INTELLIJ		}, //  E7B5  
	{ "info"			, IC_INFO			}, //  F129  
	{ "ini"				, IC_CONFIG			}, // F107B  󱁻
	{ "inl"				, IC_LANG_C			}, //  E61E  
	{ "ino"				, IC_LANG_ARDUINO	}, //  F34B  
	{ "ipt"				, IC_CAD			}, // F0EEB  󰻫
	{ "ipynb"			, IC_NOTEBOOK		}, //  E678  
	{ "iso"				, IC_DISK_IMAGE		}, //  E271  
	{ "j2c"				, IC_IMAGE			}, //  F1C5  
	{ "j2k"				, IC_IMAGE			}, //  F1C5  
	{ "jad"				, IC_LANG_JAVA		}, //  E256  
	{ "jar"				, IC_LANG_JAVA		}, //  E256  
	{ "java"			, IC_LANG_JAVA		}, //  E256  
	{ "jfi"				, IC_IMAGE			}, //  F1C5  
	{ "jfif"			, IC_IMAGE			}, //  F1C5  
	{ "jif"				, IC_IMAGE			}, //  F1C5  
	{ "jl"				, IC_JL				}, //  E624  
	{ "jmd"				, IC_MARKDOWN		}, //  F48A  
	{ "jp2"				, IC_IMAGE			}, //  F1C5  
	{ "jpe"				, IC_IMAGE			}, //  F1C5  
	{ "jpeg"			, IC_IMAGE			}, //  F1C5  
	{ "jpf"				, IC_IMAGE			}, //  F1C5  
	{ "jpg"				, IC_IMAGE			}, //  F1C5  
	{ "jpx"				, IC_IMAGE			}, //  F1C5  
	{ "js"				, IC_LANG_JSCPT		}, //  E74E  
	{ "json"			, IC_JSON			}, //  E60B  
	{ "json5"			, IC_JSON			}, //  E60B  
	{ "jsonc"			, IC_JSON			}, //  E60B  
	{ "jsx"				, IC_REACT			}, //  E7BA  
	{ "jwmrc"			, IC_JWMRC			}, //  F35B  
	{ "jxl"				, IC_IMAGE			}, //  F1C5  
	{ "kbx"				, IC_SHIELD_KEY		}, // F0BC4  󰯄
	{ "kdb"				, IC_KEYPASS		}, //  F23E  
	{ "kdbx"			, IC_KEYPASS		}, //  F23E  
	{ "kdenlive"		, IC_KDENLIVE		}, //  F33C  
	{ "kdenlivetitle"	, IC_KDENLIVE		}, //  F33C  
	{ "key"				, IC_KEY			}, //  EB11  
	{ "kicad_dru"		, IC_KICAD			}, //  F34C  
	{ "kicad_mod"		, IC_KICAD			}, //  F34C  
	{ "kicad_pcb"		, IC_KICAD			}, //  F34C  
	{ "kicad_prl"		, IC_KICAD			}, //  F34C  
	{ "kicad_pro"		, IC_KICAD			}, //  F34C  
	{ "kicad_sch"		, IC_KICAD			}, //  F34C  
	{ "kicad_sym"		, IC_KICAD			}, //  F34C  
	{ "kicad_wks"		, IC_KICAD			}, //  F34C  
	{ "ko"				, IC_OS_LINUX		}, //  F17C  
	{ "kpp"				, IC_KRITA			}, //  F33D  
	{ "kra"				, IC_KRITA			}, //  F33D  
	{ "krz"				, IC_KRITA			}, //  F33D  
	{ "ksh"				, IC_SHELL_CMD		}, //  F489  
	{ "kt"				, IC_LANG_KOTLIN	}, //  E634  
	{ "kts"				, IC_LANG_KOTLIN	}, //  E634  
	{ "latex"			, IC_LANG_TEX		}, //  E69B  
	{ "lbr"				, IC_LIBRARY		}, //  EB9C  
	{ "lck"				, IC_LOCK			}, //  F023  
	{ "ldb"				, IC_DATABASE		}, //  F1C0  
	{ "leex"			, IC_LANG_ELIXIR	}, //  E62D  
	{ "less"			, IC_LESS			}, //  E758  
	{ "lff"				, IC_FONT			}, //  F031  
	{ "lhs"				, IC_LANG_HASKELL	}, //  E777  
	{ "lib"				, IC_LIBRARY		}, //  EB9C  
	{ "license"			, IC_LICENSE		}, //  F02D  
	{ "lisp"			, IC_LISP			}, // F0172  󰅲
	{ "localized"		, IC_OS_APPLE		}, //  F179  
	{ "lock"			, IC_LOCK			}, //  F023  
	{ "log"				, IC_LOG			}, //  F18D  
	{ "lpp"				, IC_EDA_PCB		}, //  EABE  
	{ "lrc"				, IC_SUBTITLE		}, // F0A16  󰨖
	{ "ltx"				, IC_LANG_TEX		}, //  E69B  
	{ "lua"				, IC_LANG_LUA		}, //  E620  
	{ "luac"			, IC_LANG_LUA		}, //  E620  
	{ "luau"			, IC_LANG_LUA		}, //  E620  
	{ "lz"				, IC_COMPRESSED		}, //  F410  
	{ "lz4"				, IC_COMPRESSED		}, //  F410  
	{ "lzh"				, IC_COMPRESSED		}, //  F410  
	{ "lzma"			, IC_COMPRESSED		}, //  F410  
	{ "lzo"				, IC_COMPRESSED		}, //  F410  
	{ "m"				, IC_LANG_C			}, //  E61E  
	{ "m2ts"			, IC_VIDEOS			}, //  F03D  
	{ "m2v"				, IC_VIDEOS			}, //  F03D  
	{ "m3u"				, IC_PLAYLIST		}, // F0CB9  󰲹
	{ "m3u8"			, IC_PLAYLIST		}, // F0CB9  󰲹
	{ "m4a"				, IC_AUDIO			}, //  F4AE  
	{ "m4v"				, IC_VIDEOS			}, //  F03D  
	{ "magnet"			, IC_MAGNET			}, //  F076  
	{ "markdown"		, IC_MARKDOWN		}, //  F48A  
	{ "md"				, IC_MARKDOWN		}, //  F48A  
	{ "md5"				, IC_SHIELD_CHECK	}, // F0565  󰕥
	{ "mdb"				, IC_DATABASE		}, //  F1C0  
	{ "mdx"				, IC_MARKDOWN		}, //  F48A  
	{ "mid"				, IC_MID			}, // F08F2  󰣲
	{ "mjs"				, IC_LANG_JSCPT		}, //  E74E  
	{ "mk"				, IC_MAKE			}, //  E673  
	{ "mka"				, IC_AUDIO			}, //  F4AE  
	{ "mkd"				, IC_MARKDOWN		}, //  F48A  
	{ "mkv"				, IC_VIDEOS			}, //  F03D  
	{ "ml"				, IC_LANG_OCAML		}, //  E67A  
	{ "mli"				, IC_LANG_OCAML		}, //  E67A  
	{ "mll"				, IC_LANG_OCAML		}, //  E67A  
	{ "mly"				, IC_LANG_OCAML		}, //  E67A  
	{ "mm"				, IC_LANG_CPP		}, //  E61D  
	{ "mo"				, IC_TRANSLATION	}, // F05CA  󰗊
	{ "mobi"			, IC_BOOK			}, //  E28B  
	{ "mov"				, IC_VIDEOS			}, //  F03D  
	{ "mp2"				, IC_AUDIO			}, //  F4AE  
	{ "mp3"				, IC_AUDIO			}, //  F4AE  
	{ "mp4"				, IC_VIDEOS			}, //  F03D  
	{ "mpeg"			, IC_VIDEOS			}, //  F03D  
	{ "mpg"				, IC_VIDEOS			}, //  F03D  
	{ "msf"				, IC_MSF			}, //  F370  
	{ "msi"				, IC_OS_WINDOWS		}, //  F17A  
	{ "mts"				, IC_LANG_TSCPT		}, //  E628  
	{ "mustache"		, IC_MUSTACHE		}, //  E60F  
	{ "nef"				, IC_IMAGE			}, //  F1C5  
	{ "nfo"				, IC_INFO			}, //  F129  
	{ "nim"				, IC_LANG_NIM		}, //  E677  
	{ "nimble"			, IC_LANG_NIM		}, //  E677  
	{ "nims"			, IC_LANG_NIM		}, //  E677  
	{ "ninja"			, IC_NINJA			}, // F0774  󰝴
	{ "nix"				, IC_FLAKE			}, //  F313  
	{ "node"			, IC_NODEJS			}, //  E718  
	{ "norg"			, IC_NORG			}, //  E847  
	{ "nsp"				, IC_SWITCH			}, // F07E1  󰟡
	{ "nu"				, IC_SHELL_CMD		}, //  F489  
	{ "o"				, IC_BINARY			}, //  EAE8  
	{ "obj"				, IC_FILE_3D		}, // F01A7  󰆧
	{ "odb"				, IC_DATABASE		}, //  F1C0  
	{ "odf"				, IC_ODF			}, //  F37B  
	{ "odg"				, IC_ODG			}, //  F379  
	{ "odp"				, IC_ODP			}, //  F37A  
	{ "ods"				, IC_ODS			}, //  F378  
	{ "odt"				, IC_ODT			}, //  F37C  
	{ "ogg"				, IC_AUDIO			}, //  F4AE  
	{ "ogm"				, IC_VIDEOS			}, //  F03D  
	{ "ogv"				, IC_VIDEOS			}, //  F03D  
	{ "opam"			, IC_OPAM			}, // F0627  󰘧
	{ "opml"			, IC_XML			}, // F05C0  󰗀
	{ "opus"			, IC_AUDIO			}, //  F4AE  
	{ "orf"				, IC_IMAGE			}, //  F1C5  
	{ "org"				, IC_ORG			}, //  E633  
	{ "otf"				, IC_FONT			}, //  F031  
	{ "out"				, IC_OUT			}, //  EB2C  
	{ "p12"				, IC_KEY			}, //  EB11  
	{ "par"				, IC_COMPRESSED		}, //  F410  
	{ "part"			, IC_DOWNLOAD		}, // F01DA  󰇚
	{ "patch"			, IC_DIFF			}, //  F440  
	{ "pbm"				, IC_IMAGE			}, //  F1C5  
	{ "pcbdoc"			, IC_EDA_PCB		}, //  EABE  
	{ "pcm"				, IC_AUDIO			}, //  F4AE  
	{ "pdf"				, IC_PDF			}, //  F1C1  
	{ "pem"				, IC_KEY			}, //  EB11  
	{ "pfx"				, IC_KEY			}, //  EB11  
	{ "pgm"				, IC_IMAGE			}, //  F1C5  
	{ "phar"			, IC_LANG_PHP		}, //  E73D  
	{ "php"				, IC_LANG_PHP		}, //  E73D  
	{ "pkg"				, IC_PKG			}, //  EB29  
	{ "pl"				, IC_LANG_PERL		}, //  E67E  
	{ "plist"			, IC_OS_APPLE		}, //  F179  
	{ "pls"				, IC_PLAYLIST		}, // F0CB9  󰲹
	{ "plx"				, IC_LANG_PERL		}, //  E67E  
	{ "ply"				, IC_FILE_3D		}, // F01A7  󰆧
	{ "pm"				, IC_LANG_PERL		}, //  E67E  
	{ "png"				, IC_IMAGE			}, //  F1C5  
	{ "pnm"				, IC_IMAGE			}, //  F1C5  
	{ "po"				, IC_TRANSLATION	}, // F05CA  󰗊
	{ "pod"				, IC_LANG_PERL		}, //  E67E  
	{ "pot"				, IC_TRANSLATION	}, // F05CA  󰗊
	{ "pp"				, IC_PP				}, //  E631  
	{ "ppm"				, IC_IMAGE			}, //  F1C5  
	{ "pps"				, IC_SLIDE			}, //  F1C4  
	{ "ppsx"			, IC_SLIDE			}, //  F1C4  
	{ "ppt"				, IC_SLIDE			}, //  F1C4  
	{ "pptx"			, IC_SLIDE			}, //  F1C4  
	{ "prjpcb"			, IC_EDA_PCB		}, //  EABE  
	{ "procfile"		, IC_LANG_RUBY		}, //  E739  
	{ "properties"		, IC_JSON			}, //  E60B  
	{ "prql"			, IC_DATABASE		}, //  F1C0  
	{ "ps"				, IC_VECTOR			}, // F0559  󰕙
	{ "ps1"				, IC_POWERSHELL		}, //  EBC7  
	{ "psb"				, IC_PHOTOSHOP		}, //  E7B8  
	{ "psd"				, IC_PHOTOSHOP		}, //  E7B8  
	{ "psd1"			, IC_POWERSHELL		}, //  EBC7  
	{ "psf"				, IC_FONT			}, //  F031  
	{ "psm"				, IC_CAD			}, // F0EEB  󰻫
	{ "psm1"			, IC_POWERSHELL		}, //  EBC7  
	{ "pub"				, IC_PUBLIC_KEY		}, // F0DD6  󰷖
	{ "purs"			, IC_PURS			}, //  E630  
	{ "pxd"				, IC_LANG_PYTHON	}, //  E606  
	{ "pxm"				, IC_IMAGE			}, //  F1C5  
	{ "py"				, IC_LANG_PYTHON	}, //  E606  
	{ "pyc"				, IC_LANG_PYTHON	}, //  E606  
	{ "pyd"				, IC_LANG_PYTHON	}, //  E606  
	{ "pyi"				, IC_LANG_PYTHON	}, //  E606  
	{ "pyo"				, IC_LANG_PYTHON	}, //  E606  
	{ "pyw"				, IC_LANG_PYTHON	}, //  E606  
	{ "pyx"				, IC_LANG_PYTHON	}, //  E606  
	{ "qcow"			, IC_DISK_IMAGE		}, //  E271  
	{ "qcow2"			, IC_DISK_IMAGE		}, //  E271  
	{ "qm"				, IC_TRANSLATION	}, // F05CA  󰗊
	{ "qml"				, IC_QT				}, //  F375  
	{ "qrc"				, IC_QT				}, //  F375  
	{ "qss"				, IC_QT				}, //  F375  
	{ "r"				, IC_LANG_R			}, //  E68A  
	{ "rake"			, IC_LANG_RUBY		}, //  E739  
	{ "rakefile"		, IC_LANG_RUBY		}, //  E739  
	{ "rar"				, IC_COMPRESSED		}, //  F410  
	{ "raw"				, IC_IMAGE			}, //  F1C5  
	{ "razor"			, IC_RAZOR			}, //  F1FA  
	{ "rb"				, IC_LANG_RUBY		}, //  E739  
	{ "rdata"			, IC_LANG_R			}, //  E68A  
	{ "rdb"				, IC_RDB			}, //  E76D  
	{ "rdoc"			, IC_MARKDOWN		}, //  F48A  
	{ "rds"				, IC_LANG_R			}, //  E68A  
	{ "readme"			, IC_README			}, // F00BA  󰂺
	{ "rkt"				, IC_LANG_SCHEME	}, //  E6B1  
	{ "rlib"			, IC_LANG_RUST		}, //  E68B  
	{ "rmd"				, IC_MARKDOWN		}, //  E68B  
	{ "rmeta"			, IC_LANG_RUST		}, //  E68B  
	{ "rpm"				, IC_RPM			}, //  E7BB  
	{ "rs"				, IC_LANG_RUST		}, //  E68B  
	{ "rspec"			, IC_LANG_RUBY		}, //  E739  
	{ "rspec_parallel"	, IC_LANG_RUBY		}, //  E739  
	{ "rspec_status"	, IC_LANG_RUBY		}, //  E739  
	{ "rss"				, IC_RSS			}, //  F09E  
	{ "rst"				, IC_TEXT			}, //  F15C  
	{ "rtf"				, IC_TEXT			}, //  F15C  
	{ "ru"				, IC_LANG_RUBY		}, //  E739  
	{ "rubydoc"			, IC_LANG_RBRAILS	}, //  E73B  
	{ "s"				, IC_LANG_ASSEMBLY	}, //  E637  
	{ "s3db"			, IC_SQLITE			}, //  E7C4  
	{ "sal"				, IC_SQ_WAVE		}, // F147B  󱑻
	{ "sass"			, IC_LANG_SASS		}, //  E603  
	{ "sbt"				, IC_SUBTITLE		}, // F0A16  󰨖
	{ "scad"			, IC_SCAD			}, //  F34E  
	{ "scala"			, IC_SCALA			}, //  E737  
	{ "sch"				, IC_EDA_SCH		}, // F0B45  󰭅
	{ "schdoc"			, IC_EDA_SCH		}, // F0B45  󰭅
	{ "scm"				, IC_LANG_SCHEME	}, //  E6B1  
	{ "scss"			, IC_LANG_SASS		}, //  E603  
	{ "service"			, IC_SERVICE		}, //  EBA2  
	{ "sf2"				, IC_TREB_CLEF		}, // F0F70  󰽰
	{ "sfz"				, IC_TREB_CLEF		}, // F0F70  󰽰
	{ "sh"				, IC_SHELL_CMD		}, //  F489  
	{ "sha1"			, IC_SHIELD_CHECK	}, // F0565  󰕥
	{ "sha224"			, IC_SHIELD_CHECK	}, // F0565  󰕥
	{ "sha256"			, IC_SHIELD_CHECK	}, // F0565  󰕥
	{ "sha384"			, IC_SHIELD_CHECK	}, // F0565  󰕥
	{ "sha512"			, IC_SHIELD_CHECK	}, // F0565  󰕥
	{ "shell"			, IC_SHELL_CMD		}, //  F489  
	{ "shtml"			, IC_HTML5			}, //  F13B  
	{ "sig"				, IC_SIGNED_FILE	}, // F19C3  󱧃
	{ "signature"		, IC_SIGNED_FILE	}, // F19C3  󱧃
	{ "skp"				, IC_CAD			}, // F0EEB  󰻫
	{ "sl3"				, IC_SQLITE			}, //  E7C4  
	{ "sld"				, IC_LANG_SCHEME	}, //  E6B1  
	{ "sldasm"			, IC_CAD			}, // F0EEB  󰻫
	{ "sldprt"			, IC_CAD			}, // F0EEB  󰻫
	{ "slim"			, IC_LANG_RBRAILS	}, //  E73B  
	{ "sln"				, IC_VSCODE			}, //  E70C  
	{ "slvs"			, IC_CAD			}, // F0EEB  󰻫
	{ "so"				, IC_OS_LINUX		}, //  F17C  
	{ "sql"				, IC_DATABASE		}, //  F1C0  
	{ "sqlite"			, IC_SQLITE			}, //  E7C4  
	{ "sqlite3"			, IC_SQLITE			}, //  E7C4  
	{ "sr"				, IC_SQ_WAVE		}, // F147B  󱑻
	{ "srt"				, IC_SUBTITLE		}, // F0A16  󰨖
	{ "ss"				, IC_LANG_SCHEME	}, //  E6B1  
	{ "ssa"				, IC_SUBTITLE		}, // F0A16  󰨖
	{ "ste"				, IC_CAD			}, // F0EEB  󰻫
	{ "step"			, IC_CAD			}, // F0EEB  󰻫
	{ "stl"				, IC_FILE_3D		}, // F01A7  󰆧
	{ "stp"				, IC_CAD			}, // F0EEB  󰻫
	{ "sty"				, IC_LANG_TEX		}, //  E69B  
	{ "styl"			, IC_LANG_STYLUS	}, //  E600  
	{ "stylus"			, IC_LANG_STYLUS	}, //  E600  
	{ "sub"				, IC_SUBTITLE		}, // F0A16  󰨖
	{ "sublime-build"	, IC_SUBLIME		}, //  E7AA  
	{ "sublime-keymap"	, IC_SUBLIME		}, //  E7AA  
	{ "sublime-menu"	, IC_SUBLIME		}, //  E7AA  
	{ "sublime-options"	, IC_SUBLIME		}, //  E7AA  
	{ "sublime-package"	, IC_SUBLIME		}, //  E7AA  
	{ "sublime-project"	, IC_SUBLIME		}, //  E7AA  
	{ "sublime-session"	, IC_SUBLIME		}, //  E7AA  
	{ "sublime-settings", IC_SUBLIME		}, //  E7AA  
	{ "sublime-snippet"	, IC_SUBLIME		}, //  E7AA  
	{ "sublime-theme"	, IC_SUBLIME		}, //  E7AA  
	{ "suo"				, IC_VSCODE			}, //  E70C  
	{ "sv"				, IC_LANG_HDL		}, // F035B  󰍛
	{ "svelte"			, IC_SVELTE			}, //  E697  
	{ "svg"				, IC_VECTOR			}, // F0559  󰕙
	{ "svh"				, IC_LANG_HDL		}, // F035B  󰍛
	{ "swf"				, IC_AUDIO			}, //  F4AE  
	{ "swift"			, IC_SWIFT			}, //  E755  
	{ "t"				, IC_LANG_PERL		}, //  E67E  
	{ "tar"				, IC_COMPRESSED		}, //  F410  
	{ "taz"				, IC_COMPRESSED		}, //  F410  
	{ "tbc"				, IC_TCL			}, // F06D3  󰛓
	{ "tbz"				, IC_COMPRESSED		}, //  F410  
	{ "tbz2"			, IC_COMPRESSED		}, //  F410  
	{ "tc"				, IC_DISK_IMAGE		}, //  E271  
	{ "tcl"				, IC_TCL			}, // F06D3  󰛓
	{ "tex"				, IC_LANG_TEX		}, //  E69B  
	{ "tf"				, IC_TERRAFORM		}, // F1062  󱁢
	{ "tfstate"			, IC_TERRAFORM		}, // F1062  󱁢
	{ "tfvars"			, IC_TERRAFORM		}, // F1062  󱁢
	{ "tgz"				, IC_COMPRESSED		}, //  F410  
	{ "tif"				, IC_IMAGE			}, //  F1C5  
	{ "tiff"			, IC_IMAGE			}, //  F1C5  
	{ "tlz"				, IC_COMPRESSED		}, //  F410  
	{ "tml"				, IC_CONFIG			}, // F107B  󱁻
	{ "tmux"			, IC_TMUX			}, //  EBC8  
	{ "toml"			, IC_TOML			}, //  E6B2  
	{ "torrent"			, IC_TORRENT		}, //  E275  
	{ "tres"			, IC_GODOT			}, //  E65F  
	{ "ts"				, IC_LANG_TSCPT		}, //  E628  
	{ "tscn"			, IC_GODOT			}, //  E65F  
	{ "tsv"				, IC_SHEET			}, //  F1C3  
	{ "tsx"				, IC_REACT			}, //  E7BA  
	{ "ttc"				, IC_FONT			}, //  F031  
	{ "ttf"				, IC_FONT			}, //  F031  
	{ "twig"			, IC_TWIG			}, //  E61C  
	{ "txt"				, IC_TEXT			}, //  F15C  
	{ "txz"				, IC_COMPRESSED		}, //  F410  
	{ "typ"				, IC_TYPST			}, //  F37F  
	{ "tz"				, IC_COMPRESSED		}, //  F410  
	{ "tzo"				, IC_COMPRESSED		}, //  F410  
	{ "ui"				, IC_UI				}, //  F2D0  
	{ "unity"			, IC_UNITY			}, //  E721  
	{ "unity3d"			, IC_UNITY			}, //  E721  
	{ "v"				, IC_LANG_V			}, //  E6AC  
	{ "vala"			, IC_VALA			}, //  E8D1  
	{ "vdi"				, IC_DISK_IMAGE		}, //  E271  
	{ "vhd"				, IC_DISK_IMAGE		}, //  E271  
	{ "vhdl"			, IC_LANG_HDL		}, // F035B  󰍛
	{ "vhs"				, IC_VHS			}, // F0A1B  󰨛
	{ "vi"				, IC_VI				}, //  E81E  
	{ "video"			, IC_VIDEOS			}, //  F03D  
	{ "vim"				, IC_VIM			}, //  E7C5  
	{ "vmdk"			, IC_DISK_IMAGE		}, //  E271  
	{ "vob"				, IC_VIDEOS			}, //  F03D  
	{ "vsix"			, IC_VSIX			}, // F0A1E  󰨞
	{ "vue"				, IC_VUE			}, // F0844  󰡄
	{ "war"				, IC_LANG_JAVA		}, //  E256  
	{ "wav"				, IC_AUDIO			}, //  F4AE  
	{ "webm"			, IC_VIDEOS			}, //  F03D  
	{ "webmanifest"		, IC_JSON			}, //  E60B  
	{ "webp"			, IC_IMAGE			}, //  F1C5  
	{ "whl"				, IC_LANG_PYTHON	}, //  E606  
	{ "windows"			, IC_OS_WINDOWS		}, //  F17A  
	{ "wma"				, IC_AUDIO			}, //  F4AE  
	{ "wmv"				, IC_VIDEOS			}, //  F03D  
	{ "woff"			, IC_FONT			}, //  F031  
	{ "woff2"			, IC_FONT			}, //  F031  
	{ "wrl"				, IC_FILE_3D		}, // F01A7  󰆧
	{ "wrz"				, IC_FILE_3D		}, // F01A7  󰆧
	{ "wv"				, IC_AUDIO			}, //  F4AE  
	{ "x_b"				, IC_CAD			}, // F0EEB  󰻫
	{ "x_t"				, IC_CAD			}, // F0EEB  󰻫
	{ "xaml"			, IC_XAML			}, // F0673  󰙳
	{ "xcf"				, IC_GIMP			}, //  F338  
	{ "xci"				, IC_SWITCH			}, // F07E1  󰟡
	{ "xcplayground"	, IC_SWIFT			}, //  E755  
	{ "xhtml"			, IC_HTML5			}, //  F13B  
	{ "xlr"				, IC_SHEET			}, //  F1C3  
	{ "xls"				, IC_SHEET			}, //  F1C3  
	{ "xlsm"			, IC_SHEET			}, //  F1C3  
	{ "xlsx"			, IC_SHEET			}, //  F1C3  
	{ "xml"				, IC_XML			}, // F05C0  󰗀
	{ "xpi"				, IC_XPI			}, //  EAE6  
	{ "xpm"				, IC_IMAGE			}, //  F1C5  
	{ "xul"				, IC_XML			}, // F05C0  󰗀
	{ "xz"				, IC_COMPRESSED		}, //  F410  
	{ "yaml"			, IC_YAML			}, //  E6A8  
	{ "yml"				, IC_YAML			}, //  E6A8  
	{ "z"				, IC_COMPRESSED		}, //  F410  
	{ "z64"				, IC_GBA			}, // F1393  󱎓
	{ "zig"				, IC_ZIG			}, //  E6A9  
	{ "zip"				, IC_COMPRESSED		}, //  F410  
	{ "zsh"				, IC_SHELL_CMD		}, //  F489  
	{ "zsh-theme"		, IC_SHELL			}, // F1183  󱆃
	{ "zst"				, IC_COMPRESSED		}, //  F410  
};

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignoreRegexp /((?<=\bIC_)\w+|\b[0-9A-F]{4,5})\b|(?<=\{[ \t]+")[\w-.]+(?=")/g
