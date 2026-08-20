/// @file icons/definitions.c

#include "icons.h"

/* —— Base Icon Definitions ———————————————————————————————————————————————————————————————————————————————————————— */

#define IC_FILE				L'' /*  F15B  	[ • • • ] */
#define IC_FILE_UNKNOWN		L'󰡯' /* F086F  󰡯	  [ • • • ] */

#define IC_FOLDER			L'' /*  E5FF  	[ • • • ] */
#define IC_FOLDER_OPEN		L'' /*  F115  	[ • • • ] */

#define IC_ACF				L'' /*  F1B6  	[ • • E ] */
#define IC_AI				L'' /*  E7B4  	[ • • E ] */
#define IC_ARCHBTW			L'' /*  F303  	[ • F • ] */
#define IC_ASP				L'' /*  F121  	[ • • E ] */
#define IC_ATOM				L'' /*  E764  	[ • F • ] */
#define IC_AUDIO			L'' /*  F001  	[ • • E ] */
#define IC_BINARY			L'' /*  EAE8  	[ • • E ] */
#define IC_BLEND			L'󰂫' /* F00AB  󰂫	  [ • • E ] */
#define IC_BOOK				L'' /*  E28B  	[ • • E ] */
#define IC_BSPWM			L'' /*  F355  	[ • F • ] */
#define IC_BUN				L'' /*  E76F  	[ • F • ] */
#define IC_CACHE			L'' /*  F49B  	[ • • E ] */
#define IC_CAD				L'󰻫' /* F0EEB  󰻫	  [ • • E ] */
#define IC_CALENDAR			L'' /*  EAB0  	[ • • E ] */
#define IC_CLOCK			L'' /*  F43A  	[ • F • ] */
#define IC_CLOJURE_1		L'' /*  E768  	[ • • E ] */
#define IC_BACKUP_DIR		L'󰴋' /* F0D0B  󰴋	  [ D • • ] */
#define IC_CLOJURE_2		L'' /*  E76A  	[ • • E ] */
#define IC_CMAKE			L'' /*  E794  	[ • F E ] */
#define IC_CODE_OF_CONDUCT	L'' /*  F4AE  	[ • F • ] */
#define IC_CODESPELL		L'󰓆' /* F04C6  󰓆	  [ • F • ] */
#define IC_COFFEE			L'' /*  F0F4  	[ • • E ] */
#define IC_COM				L'' /*  E629  	[ • • E ] */
#define IC_COMPRESSED		L'' /*  F410  	[ • • E ] */
#define IC_CONDA			L'' /*  E715  	[ • F E ] */
#define IC_CONFIG			L'󱁻' /* F107B  󱁻	  [ • F E ] */
#define IC_CONTACTS			L'󰉌' /* F024C  󰉌	  [ D • • ] */
#define IC_COW				L'󰆚' /* F019A  󰆚	  [ • • E ] */
#define IC_CR				L'' /*  E62F  	[ • • E ] */
#define IC_CSS3				L'' /*  E749  	[ • • E ] */
#define IC_CSV				L'' /*  EEFC  	[ • • E ] */
#define IC_CU				L'' /*  E64B  	[ • • E ] */
#define IC_DART				L'' /*  E798  	[ • • E ] */
#define IC_DATABASE			L'' /*  F1C0  	[ • • E ] */
#define IC_DEB				L'' /*  E77D  	[ • • E ] */
#define IC_DESKTOP			L'' /*  F108  	[ D • • ] */
#define IC_DESKTOP_EXT		L'' /*  EBD1  	[ • • E ] */
#define IC_DIFF				L'' /*  F440  	[ • • E ] */
#define IC_DISK_IMAGE		L'' /*  E271  	[ • • E ] */
#define IC_DOCKER			L'' /*  E650  	[ • F E ] */
#define IC_DOCUMENT			L'' /*  F1C2  	[ • • E ] */
#define IC_DOCUMENTS		L'󰲂' /* F0C82  󰲂	  [ D • • ] */
#define IC_DOWNLOAD			L'󰇚' /* F01DA  󰇚	  [ • • E ] */
#define IC_DOWNLOADS		L'󰉍' /* F024D  󰉍	  [ D • • ] */
#define IC_DRAWIO			L'' /*  EBBA  	[ • • E ] */
#define IC_DROPBOX			L'' /*  E707  	[ • F • ] */
#define IC_EARTH			L'' /*  F0AC  	[ • F • ] */
#define IC_EBUILD			L'' /*  F30D  	[ • • E ] */
#define IC_EDA_PCB			L'' /*  EABE  	[ • • E ] */
#define IC_EDA_SCH			L'󰭅' /* F0B45  󰭅	  [ • • E ] */
#define IC_EDITORCONFIG		L'' /*  E652  	[ • F E ] */
#define IC_EJS				L'' /*  E618  	[ • • E ] */
#define IC_ELM				L'' /*  E62C  	[ • • E ] */
#define IC_EMACS			L'' /*  E632  	[ • F E ] */
#define IC_EML				L'' /*  F003  	[ • • E ] */
#define IC_ENV				L'' /*  F462  	[ • F E ] */
#define IC_ERLANG			L'' /*  E7B1  	[ • • E ] */
#define IC_ESLINT			L'' /*  E655  	[ • F • ] */
#define IC_EXERCISM			L'' /*  EBE5  	[ D • • ] */
#define IC_FAVORITES		L'󰚝' /* F069D  󰚝	  [ D • • ] */
#define IC_FILE_3D			L'󰆧' /* F01A7  󰆧	  [ • • E ] */
#define IC_FLAKE			L'' /*  F313  	[ • F E ] */
#define IC_FOLDER_BUILD		L'󱧼' /* F19FC  󱧼	  [ D • • ] */
#define IC_FOLDER_CONFIG	L'' /*  E5FC  	[ D • • ] */
#define IC_FOLDER_GIT		L'' /*  E5FB  	[ D • • ] */
#define IC_FOLDER_GITHUB	L'' /*  E5FD  	[ D • • ] */
#define IC_FOLDER_HIDDEN	L'󱞞' /* F179E  󱞞	  [ D • • ] */
#define IC_FOLDER_KEY		L'󰢬' /* F08AC  󰢬	  [ D • • ] */
#define IC_FOLDER_NPM		L'' /*  E5FA  	[ D • • ] */
#define IC_FONT				L'' /*  F031  	[ • F E ] */
#define IC_FREECAD			L'' /*  F336  	[ • F E ] */
#define IC_GBA				L'󱎓' /* F1393  󱎓	  [ • • E ] */
#define IC_GCODE			L'󰫴' /* F0AF4  󰫴	  [ • • E ] */
#define IC_GFORM			L'' /*  F298  	[ • • E ] */
#define IC_GIMP				L'' /*  F338  	[ • • E ] */
#define IC_GIST_SECRET		L'' /*  EAFA  	[ • • E ] */
#define IC_GIT				L'󰊢' /* F02A2  󰊢	  [ • F E ] */
#define IC_GITLAB			L'' /*  F296  	[ • F • ] */
#define IC_GODOT			L'' /*  E65F  	[ • • E ] */
#define IC_GOOGLE_CLOUD		L'󱇶' /* F11F6  󱇶	  [ • F • ] */
#define IC_GRADLE			L'' /*  E660  	[ • F E ] */
#define IC_GRAPH			L'󱁉' /* F1049  󱁉	  [ • • E ] */
#define IC_GRAPHQL			L'' /*  E662  	[ • • E ] */
#define IC_GRUNT			L'' /*  E611  	[ • F • ] */
#define IC_GTK				L'' /*  F362  	[ • • E ] */
#define IC_GULP				L'' /*  E610  	[ • F • ] */
#define IC_HAML				L'' /*  E664  	[ • • E ] */
#define IC_HEROKU			L'' /*  E77B  	[ • F • ] */
#define IC_HEX				L'󱊧' /* F12A7  󱊧	  [ • • E ] */
#define IC_HOME				L'󱂵' /* F10B5  󱂵	  [ D • • ] */
#define IC_HOMEBREW			L'󱄖' /* F1116  󱄖	  [ • F • ] */
#define IC_HOOK				L'󰛢' /* F06E2  󰛢	  [ • F • ] */
#define IC_HTML5			L'' /*  F13B  	[ • • E ] */
#define IC_HYPRLAND			L'' /*  F359  	[ • F • ] */
#define IC_I3				L'' /*  F35A  	[ • F • ] */
#define IC_IMAGE			L'' /*  F1C5  	[ • • E ] */
#define IC_INFO				L'' /*  F129  	[ • • E ] */
#define IC_INTELLIJ			L'' /*  E7B5  	[ • F E ] */
#define IC_JENKINSFILE		L'' /*  E66E  	[ • F • ] */
#define IC_JL				L'' /*  E624  	[ • • E ] */
#define IC_JSON				L'' /*  E60B  	[ • • E ] */
#define IC_JWMRC			L'' /*  F35B  	[ • • E ] */
#define IC_KDE				L'' /*  F373  	[ • F • ] */
#define IC_KDENLIVE			L'' /*  F33C  	[ • F E ] */
#define IC_KEY				L'' /*  EB11  	[ • • E ] */
#define IC_KEYPASS			L'' /*  F23E  	[ • • E ] */
#define IC_KICAD			L'' /*  F34C  	[ • F E ] */
#define IC_KRITA			L'' /*  F33D  	[ • F E ] */
#define IC_LANG_ARDUINO		L'' /*  F34B  	[ • • E ] */
#define IC_LANG_ASSEMBLY	L'' /*  E637  	[ • • E ] */
#define IC_LANG_C			L'' /*  E61E  	[ • • E ] */
#define IC_LANG_CPP			L'' /*  E61D  	[ • • E ] */
#define IC_LANG_CSHARP		L'󰌛' /* F031B  󰌛	  [ • • E ] */
#define IC_LANG_D			L'' /*  E7AF  	[ • • E ] */
#define IC_LANG_ELIXIR		L'' /*  E62D  	[ • F E ] */
#define IC_LANG_FENNEL		L'' /*  E6AF  	[ • F E ] */
#define IC_LANG_FORTRAN		L'󱈚' /* F121A  󱈚	  [ • • E ] */
#define IC_LANG_FSHARP		L'' /*  E7A7  	[ • • E ] */
#define IC_LANG_GLEAM		L'󰦥' /* F09A5  󰦥	  [ • • E ] */
#define IC_LANG_GO			L'' /*  E65E  	[ • F E ] */
#define IC_LANG_GROOVY		L'' /*  E775  	[ • • E ] */
#define IC_LANG_HASKELL		L'' /*  E777  	[ D • E ] */
#define IC_LANG_HDL			L'󰍛' /* F035B  󰍛	  [ • • E ] */
#define IC_LANG_HOLYC		L'󰂢' /* F00A2  󰂢	  [ • • E ] */
#define IC_LANG_JAVA		L'' /*  E256  	[ • • E ] */
#define IC_LANG_JSCPT		L'' /*  E74E  	[ • F E ] */
#define IC_LANG_KOTLIN		L'' /*  E634  	[ • • E ] */
#define IC_LANG_LUA			L'' /*  E620  	[ • • E ] */
#define IC_LANG_NIM			L'' /*  E677  	[ • • E ] */
#define IC_LANG_OCAML		L'' /*  E67A  	[ D F E ] */
#define IC_LANG_PERL		L'' /*  E67E  	[ • • E ] */
#define IC_LANG_PHP			L'' /*  E73D  	[ • F E ] */
#define IC_LANG_PYTHON		L'' /*  E606  	[ • F E ] */
#define IC_LANG_R			L'' /*  E68A  	[ • • E ] */
#define IC_LANG_RBRAILS		L'' /*  E73B  	[ • F E ] */
#define IC_LANG_RUBY		L'' /*  E739  	[ • F E ] */
#define IC_LANG_RUST		L'' /*  E68B  	[ • F E ] */
#define IC_LANG_SASS		L'' /*  E603  	[ • • E ] */
#define IC_LANG_SCHEME		L'' /*  E6B1  	[ • • E ] */
#define IC_LANG_STYLUS		L'' /*  E600  	[ • • E ] */
#define IC_LANG_TEX			L'' /*  E69B  	[ • • E ] */
#define IC_LANG_TSCPT		L'' /*  E628  	[ • F E ] */
#define IC_LANG_V			L'' /*  E6AC  	[ • • E ] */
#define IC_LESS				L'' /*  E758  	[ • • E ] */
#define IC_LIBRARY			L'' /*  EB9C  	[ • • E ] */
#define IC_LICENSE			L'' /*  F02D  	[ • F E ] */
#define IC_LISP				L'󰅲' /* F0172  󰅲	  [ • • E ] */
#define IC_LOCK				L'' /*  F023  	[ • F E ] */
#define IC_LOG				L'' /*  F18D  	[ • F E ] */
#define IC_LXDE				L'' /*  F363  	[ • F • ] */
#define IC_LXQT				L'' /*  F364  	[ • F • ] */
#define IC_MAGNET			L'' /*  F076  	[ • • E ] */
#define IC_MAIL				L'󰇰' /* F01F0  󰇰	  [ D • • ] */
#define IC_MAKE				L'' /*  E673  	[ • F E ] */
#define IC_MARKDOWN			L'' /*  F48A  	[ • • E ] */
#define IC_MID				L'󰣲' /* F08F2  󰣲	  [ • • E ] */
#define IC_MOVIES			L'󰿎' /* F0FCE  󰿎	  [ D • • ] */
#define IC_MPV				L'' /*  F36E  	[ • F • ] */
#define IC_MSF				L'' /*  F370  	[ • • E ] */
#define IC_MUSIC			L'󱍙' /* F1359  󱍙	  [ D • • ] */
#define IC_MUSTACHE			L'' /*  E60F  	[ • • E ] */
#define IC_NANO				L'' /*  E838  	[ • F • ] */
#define IC_NEWS				L'' /*  F1EA  	[ • F • ] */
#define IC_NINJA			L'󰝴' /* F0774  󰝴	  [ • • E ] */
#define IC_NODEJS			L'' /*  E718  	[ • F E ] */
#define IC_NORG				L'' /*  E847  	[ • • E ] */
#define IC_NOTEBOOK			L'' /*  E678  	[ • • E ] */
#define IC_NPM				L'' /*  E71E  	[ • F • ] */
#define IC_NUXT				L'󱄆' /* F1106  󱄆	  [ • F • ] */
#define IC_ODF				L'' /*  F37B  	[ • • E ] */
#define IC_ODG				L'' /*  F379  	[ • • E ] */
#define IC_ODP				L'' /*  F37A  	[ • • E ] */
#define IC_ODS				L'' /*  F378  	[ • • E ] */
#define IC_ODT				L'' /*  F37C  	[ • • E ] */
#define IC_OPAM				L'󰘧' /* F0627  󰘧	  [ • • E ] */
#define IC_ORG				L'' /*  E633  	[ • • E ] */
#define IC_OS_ANDROID		L'' /*  E70E  	[ • • E ] */
#define IC_OS_APPLE			L'' /*  F179  	[ • F E ] */
#define IC_OS_LINUX			L'' /*  F17C  	[ • • E ] */
#define IC_OS_WINDOWS		L'' /*  F17A  	[ • • E ] */
#define IC_OS_WINDOWS_CMD	L'' /*  EBC4  	[ • • E ] */
#define IC_OUT				L'' /*  EB2C  	[ • • E ] */
#define IC_PAINTBRUSH		L'' /*  EE72  	[ • F • ] */
#define IC_PDF				L'' /*  F1C1  	[ • • E ] */
#define IC_PEOPLE			L'' /*  EDCA  	[ • F • ] */
#define IC_PHOTOSHOP		L'' /*  E7B8  	[ • • E ] */
#define IC_PICTURES			L'󰉏' /* F024F  󰉏	  [ D • • ] */
#define IC_PKG				L'' /*  EB29  	[ • • E ] */
#define IC_PLATFORMIO		L'' /*  E682  	[ • F • ] */
#define IC_PLAYLIST			L'󰲹' /* F0CB9  󰲹	  [ • • E ] */
#define IC_POM				L'' /*  E674  	[ • F • ] */
#define IC_POWERSHELL		L'' /*  EBC7  	[ • • E ] */
#define IC_PP				L'' /*  E631  	[ • • E ] */
#define IC_PRETTIER			L'' /*  E6B4  	[ • F • ] */
#define IC_PRIVATE_KEY		L'󰌆' /* F0306  󰌆	  [ • F • ] */
#define IC_PRUSASLICER		L'' /*  F351  	[ • F • ] */
#define IC_PUBLIC_KEY		L'󰷖' /* F0DD6  󰷖	  [ • • E ] */
#define IC_PURS				L'' /*  E630  	[ • • E ] */
#define IC_QT				L'' /*  F375  	[ • F E ] */
#define IC_RAZOR			L'' /*  F1FA  	[ • • E ] */
#define IC_RDB				L'' /*  E76D  	[ • • E ] */
#define IC_REACT			L'' /*  E7BA  	[ • • E ] */
#define IC_README			L'󰂺' /* F00BA  󰂺	  [ • F E ] */
#define IC_RENOVATE			L'󰉼' /* F027C  󰉼	  [ • F • ] */
#define IC_ROBOT			L'󰚩' /* F06A9  󰚩	  [ • F • ] */
#define IC_RPM				L'' /*  E7BB  	[ • • E ] */
#define IC_RSS				L'' /*  F09E  	[ • • E ] */
#define IC_SCAD				L'' /*  F34E  	[ • • E ] */
#define IC_SCALA			L'' /*  E737  	[ • • E ] */
#define IC_SECURITY			L'󰒃' /* F0483  󰒃	  [ • F • ] */
#define IC_SERVICE			L'' /*  EBA2  	[ • • E ] */
#define IC_SHEET			L'' /*  F1C3  	[ • • E ] */
#define IC_SHELL			L'󱆃' /* F1183  󱆃	  [ • F E ] */
#define IC_SHELL_CMD		L'' /*  F489  	[ • F E ] */
#define IC_SHIELD_CHECK		L'󰕥' /* F0565  󰕥	  [ • • E ] */
#define IC_SHIELD_KEY		L'󰯄' /* F0BC4  󰯄	  [ • • E ] */
#define IC_SHIELD_LOCK		L'󰦝' /* F099D  󰦝	  [ • • E ] */
#define IC_SIGNED_FILE		L'󱧃' /* F19C3  󱧃	  [ • • E ] */
#define IC_SLIDE			L'' /*  F1C4  	[ • • E ] */
#define IC_SQ_WAVE			L'󱑻' /* F147B  󱑻	  [ • • E ] */
#define IC_SQLITE			L'' /*  E7C4  	[ • • E ] */
#define IC_SRC				L'󰣞' /* F08DE  󰣞	  [ D • • ] */
#define IC_SSH_LOGO			L'󰣀' /* F08C0  󰣀	  [ • F • ] */
#define IC_STAR				L'' /*  E623  	[ • F • ] */
#define IC_STOW				L'' /*  EEF1  	[ • F • ] */
#define IC_SUBLIME			L'' /*  E7AA  	[ • • E ] */
#define IC_SUBTITLE			L'󰨖' /* F0A16  󰨖	  [ • • E ] */
#define IC_SVELTE			L'' /*  E697  	[ • • E ] */
#define IC_SWIFT			L'' /*  E755  	[ • • E ] */
#define IC_SWITCH			L'󰟡' /* F07E1  󰟡	  [ • • E ] */
#define IC_TCL				L'󰛓' /* F06D3  󰛓	  [ • • E ] */
#define IC_TERRAFORM		L'󱁢' /* F1062  󱁢	  [ • • E ] */
#define IC_TEXT				L'' /*  F15C  	[ • • E ] */
#define IC_TMUX				L'' /*  EBC8  	[ • F E ] */
#define IC_TODO				L'' /*  F0AE  	[ • F • ] */
#define IC_TOML				L'' /*  E6B2  	[ • • E ] */
#define IC_TORRENT			L'' /*  E275  	[ • • E ] */
#define IC_TRANSLATION		L'󰗊' /* F05CA  󰗊	  [ • • E ] */
#define IC_TRASH			L'' /*  F1F8  	[ D • • ] */
#define IC_TREB_CLEF		L'󰽰' /* F0F70  󰽰	  [ • • E ] */
#define IC_TWIG				L'' /*  E61C  	[ • • E ] */
#define IC_TYPST			L'' /*  F37F  	[ • • E ] */
#define IC_UI				L'' /*  F2D0  	[ • • E ] */
#define IC_UNITY			L'' /*  E721  	[ • • E ] */
#define IC_VAGRANT			L'⍱' /*  2371  ⍱	[ • F • ] */
#define IC_VALA				L'' /*  E8D1  	[ • • E ] */
#define IC_VECTOR			L'󰕙' /* F0559  󰕙	  [ • • E ] */
#define IC_VHS				L'󰨛' /* F0A1B  󰨛	  [ • • E ] */
#define IC_VI				L'' /*  E81E  	[ • • E ] */
#define IC_VIDEOS			L'' /*  F03D  	[ D • E ] */
#define IC_VIM				L'' /*  E7C5  	[ • F E ] */
#define IC_VLC				L'󰕼' /* F057C  󰕼	  [ • F • ] */
#define IC_VSCODE			L'' /*  E70C  	[ • • E ] */
#define IC_VSIX				L'󰨞' /* F0A1E  󰨞	  [ • • E ] */
#define IC_VUE				L'󰡄' /* F0844  󰡄	  [ • • E ] */
#define IC_WEBPACK			L'󰜫' /* F072B  󰜫	  [ • F • ] */
#define IC_WESTON			L'' /*  F367  	[ • F • ] */
#define IC_WRENCH			L'' /*  F0AD  	[ • F • ] */
#define IC_XAML				L'󰙳' /* F0673  󰙳	  [ • • E ] */
#define IC_XML				L'󰗀' /* F05C0  󰗀	  [ • • E ] */
#define IC_XORG				L'' /*  F369  	[ • F • ] */
#define IC_XPI				L'' /*  EAE6  	[ • • E ] */
#define IC_YAML				L'' /*  E8EB  	[ • • • ] */
#define IC_YARN				L'' /*  E6A7  	[ • F • ] */
#define IC_ZIG				L'' /*  E6A9  	[ • F E ] */

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— Default Icons ———————————————————————————————————————————————————————————————————————————————————————————————— */

const icon_t DEFAULT_FILE_ICON = IC_FILE;
const icon_t UNKNOWN_EXT_ICON  = IC_FILE_UNKNOWN;
const icon_t DEFAULT_DIR_ICON  = IC_FOLDER;

/* —— Directory Icons —————————————————————————————————————————————————————————————————————————————————————————————— */

/// An array containing the basenames of directories, and their associated icons.
/// This array should contain all the directories that have custom icons.
const Icon DIRNAME_ICONS[] = {
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
	{ "source"			, IC_SRC			}, // F08DE  󰣞  – JV
	{ "ssh"				, IC_FOLDER_KEY		}, // F08AC  󰢬
	{ "sudoers.d"		, IC_FOLDER_KEY		}, // F08AC  󰢬
	{ "Videos"			, IC_VIDEOS			}, //  F03D  
	{ "xbps.d"			, IC_FOLDER_CONFIG	}, //  E5FC  
	{ "xorg.conf.d"		, IC_FOLDER_CONFIG	}, //  E5FC  
	END_OF_ICONS
};

/* —— Filename Icons ——————————————————————————————————————————————————————————————————————————————————————————————— */

/// Array containing full filenames & their icons.
const Icon FILENAME_ICONS[] = {
	{ "._ds_store"					, IC_OS_APPLE			}, //  F179  
	{ ".aliases"					, IC_SHELL				}, // F1183  󱆃
	{ ".atom"						, IC_ATOM				}, //  E764  
	{ ".bash_aliases"				, IC_SHELL				}, // F1183  󱆃
	{ ".bash_history"				, IC_SHELL				}, // F1183  󱆃
	{ ".bash_logout"				, IC_SHELL				}, // F1183  󱆃
	{ ".bash_profile"				, IC_SHELL				}, // F1183  󱆃
	{ ".bashrc"						, IC_SHELL				}, // F1183  󱆃
	{ ".cfusertextencoding"			, IC_OS_APPLE			}, //  F179  
	{ ".clang-format"				, IC_CONFIG				}, // F107B  󱁻
	{ ".clang-tidy"					, IC_CONFIG				}, // F107B  󱁻
	{ ".codespellrc"				, IC_CODESPELL			}, // F04C6  󰓆
	{ ".condarc"					, IC_CONDA				}, //  E715  
	{ ".cshrc"						, IC_SHELL				}, // F1183  󱆃
	{ ".ds_store"					, IC_OS_APPLE			}, //  F179  
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
	{ ".srcinfo"					, IC_ARCHBTW			}, //  F303  
	{ ".stowrc"						, IC_STOW				}, //  EEF1  
	{ ".tcshrc"						, IC_SHELL				}, // F1183  󱆃
	{ ".viminfo"					, IC_VIM				}, //  E7C5  
	{ ".vimrc"						, IC_VIM				}, //  E7C5  
	{ ".xauthority"					, IC_XORG				}, //  F369  
	{ ".xinitrc"					, IC_XORG				}, //  F369  
	{ ".xresources"					, IC_XORG				}, //  F369  
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
	{ "authors"						, IC_PEOPLE				}, //  EDCA  
	{ "authors.txt"					, IC_PEOPLE				}, //  EDCA  
	{ "bashrc"						, IC_SHELL				}, // F1183  󱆃
	{ "brewfile"					, IC_HOMEBREW			}, // F1116  󱄖
	{ "brewfile.lock.json"			, IC_HOMEBREW			}, // F1116  󱄖
	{ "bspwmrc"						, IC_BSPWM				}, //  F355  
	{ "build.gradle.kts"			, IC_GRADLE				}, //  E660  
	{ "build.zig.zon"				, IC_ZIG				}, //  E6A9  
	{ "bun.lockb"					, IC_BUN				}, //  E76F  
	{ "cantorrc"					, IC_KDE				}, //  F373  
	{ "cargo.lock"					, IC_LANG_RUST			}, //  E68B  
	{ "cargo.toml"					, IC_LANG_RUST			}, //  E68B  
	{ "changelog"					, IC_NEWS				}, //  F1EA  
	{ "changelog.md"				, IC_NEWS				}, //  F1EA  
	{ "changes"						, IC_NEWS				}, //  F1EA  
	{ "changes.md"					, IC_NEWS				}, //  F1EA  
	{ "cmakelists.txt"				, IC_CMAKE				}, //  E794  
	{ "code_of_conduct"				, IC_CODE_OF_CONDUCT	}, //  F4AE  
	{ "code_of_conduct.md"			, IC_CODE_OF_CONDUCT	}, //  F4AE  
	{ "commit_editmsg"				, IC_GIT				}, // F02A2  󰊢
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
	{ "copying"						, IC_LICENSE			}, //  F02D  
	{ "copyright"					, IC_LICENSE			}, //  F02D  
	{ "crontab"						, IC_CONFIG				}, // F107B  󱁻
	{ "crypttab"					, IC_CONFIG				}, // F107B  󱁻
	{ "csh.cshrc"					, IC_SHELL				}, // F1183  󱆃
	{ "csh.login"					, IC_SHELL				}, // F1183  󱆃
	{ "csh.logout"					, IC_SHELL				}, // F1183  󱆃
	{ "docker-compose.yaml"			, IC_DOCKER				}, //  E650  
	{ "docker-compose.yml"			, IC_DOCKER				}, //  E650  
	{ "dockerfile"					, IC_DOCKER				}, //  E650  
	{ "dropbox"						, IC_DROPBOX			}, //  E707  
	{ "dune"						, IC_LANG_OCAML			}, //  E67A  
	{ "dune-project"				, IC_WRENCH				}, //  F0AD  
	{ "earthfile"					, IC_EARTH				}, //  F0AC  
	{ "environment"					, IC_CONFIG				}, // F107B  󱁻
	{ "favicon.ico"					, IC_STAR				}, //  E623  
	{ "fennelrc"					, IC_LANG_FENNEL		}, //  E6AF  
	{ "flake.lock"					, IC_FLAKE				}, //  F313  
	{ "fonts.conf"					, IC_FONT				}, //  F031  
	{ "fp-info-cache"				, IC_KICAD				}, //  F34C  
	{ "fp-lib-table"				, IC_KICAD				}, //  F34C  
	{ "freecad.conf"				, IC_FREECAD			}, //  F336  
	{ "gemfile"						, IC_LANG_RUBY			}, //  E739  
	{ "gemfile.lock"				, IC_LANG_RUBY			}, //  E739  
	{ "gnumakefile"					, IC_MAKE				}, //  E673  
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
	{ "jenkinsfile"					, IC_JENKINSFILE		}, //  E66E  
	{ "jsconfig.json"				, IC_LANG_JSCPT			}, //  E74E  
	{ "justfile"					, IC_WRENCH				}, //  F0AD  
	{ "justfile"					, IC_WRENCH				}, //  F0AD  
	{ "kalgebrarc"					, IC_KDE				}, //  F373  
	{ "kdeglobals"					, IC_KDE				}, //  F373  
	{ "kdenlive-layoutsrc"			, IC_KDENLIVE			}, //  F33C  
	{ "kdenliverc"					, IC_KDENLIVE			}, //  F33C  
	{ "known_hosts"					, IC_SSH_LOGO			}, // F08C0  󰣀
	{ "kritadisplayrc"				, IC_KRITA				}, //  F33D  
	{ "kritarc"						, IC_KRITA				}, //  F33D  
	{ "licence"						, IC_LICENSE			}, //  F02D  
	{ "licence.md"					, IC_LICENSE			}, //  F02D  
	{ "licence.txt"					, IC_LICENSE			}, //  F02D  
	{ "license"						, IC_LICENSE			}, //  F02D  
	{ "license-apache"				, IC_LICENSE			}, //  F02D  
	{ "license-mit"					, IC_LICENSE			}, //  F02D  
	{ "license.md"					, IC_LICENSE			}, //  F02D  
	{ "license.txt"					, IC_LICENSE			}, //  F02D  
	{ "localized"					, IC_OS_APPLE			}, //  F179  
	{ "localtime"					, IC_CLOCK				}, //  F43A  
	{ "lock"						, IC_LOCK				}, //  F023  
	{ "lock"						, IC_LOCK				}, //  F023  
	{ "log"							, IC_LOG				}, //  F18D  
	{ "log"							, IC_LOG				}, //  F18D  
	{ "lxde-rc.xml"					, IC_LXDE				}, //  F363  
	{ "lxqt.conf"					, IC_LXQT				}, //  F364  
	{ "makefile"					, IC_MAKE				}, //  E673  
	{ "makefile"					, IC_MAKE				}, //  E673  
	{ "makefile.ac"					, IC_MAKE				}, //  E673  
	{ "makefile.am"					, IC_MAKE				}, //  E673  
	{ "makefile.in"					, IC_MAKE				}, //  E673  
	{ "manifest"					, IC_LANG_PYTHON		}, //  E606  
	{ "manifest.in"					, IC_LANG_PYTHON		}, //  E606  
	{ "mix.lock"					, IC_LANG_ELIXIR		}, //  E62D  
	{ "mpv.conf"					, IC_MPV				}, //  F36E  
	{ "news"						, IC_NEWS				}, //  F1EA  
	{ "news.md"						, IC_NEWS				}, //  F1EA  
	{ "npm-shrinkwrap.json"			, IC_NPM				}, //  E71E  
	{ "npmrc"						, IC_NPM				}, //  E71E  
	{ "package-lock.json"			, IC_NPM				}, //  E71E  
	{ "package.json"				, IC_NPM				}, //  E71E  
	{ "passwd"						, IC_LOCK				}, //  F023  
	{ "php.ini"						, IC_LANG_PHP			}, //  E73D  
	{ "pkgbuild"					, IC_ARCHBTW			}, //  F303  
	{ "platformio.ini"				, IC_PLATFORMIO			}, //  E682  
	{ "pom.xml"						, IC_POM				}, //  E674  
	{ "procfile"					, IC_HEROKU				}, //  E77B  
	{ "profile"						, IC_SHELL				}, // F1183  󱆃
	{ "prusaslicer.ini"				, IC_PRUSASLICER		}, //  F351  
	{ "prusaslicergcodeviewer.ini"	, IC_PRUSASLICER		}, //  F351  
	{ "pyproject.toml"				, IC_LANG_PYTHON		}, //  E606  
	{ "pyvenv.cfg"					, IC_LANG_PYTHON		}, //  E606  
	{ "qt5ct.conf"					, IC_QT					}, //  F375  
	{ "qt6ct.conf"					, IC_QT					}, //  F375  
	{ "qtproject.conf"				, IC_QT					}, //  F375  
	{ "rakefile"					, IC_LANG_RUBY			}, //  E739  
	{ "readme"						, IC_README				}, // F00BA  󰂺
	{ "readme.md"					, IC_README				}, // F00BA  󰂺
	{ "release.toml"				, IC_LANG_RUST			}, //  E68B  
	{ "renovate.json"				, IC_RENOVATE			}, // F027C  󰉼
	{ "requirements.txt"			, IC_LANG_PYTHON		}, //  E606  
	{ "robots.txt"					, IC_ROBOT				}, // F06A9  󰚩
	{ "rubydoc"						, IC_LANG_RBRAILS		}, //  E73B  
	{ "rvmrc"						, IC_LANG_RUBY			}, //  E739  
	{ "security"					, IC_SECURITY			}, // F0483  󰒃
	{ "security.md"					, IC_SECURITY			}, // F0483  󰒃
	{ "settings.gradle.kts"			, IC_GRADLE				}, //  E660  
	{ "shadow"						, IC_LOCK				}, //  F023  
	{ "shells"						, IC_CONFIG				}, // F107B  󱁻
	{ "sudoers"						, IC_LOCK				}, //  F023  
	{ "sxhkdrc"						, IC_CONFIG				}, // F107B  󱁻
	{ "sym-lib-table"				, IC_KICAD				}, //  F34C  
	{ "timezone"					, IC_CLOCK				}, //  F43A  
	{ "tmux.conf"					, IC_TMUX				}, //  EBC8  
	{ "tmux.conf.local"				, IC_TMUX				}, //  EBC8  
	{ "todo"						, IC_TODO				}, //  F0AE  
	{ "todo.md"						, IC_TODO				}, //  F0AE  
	{ "tsconfig.json"				, IC_LANG_TSCPT			}, //  E628  
	{ "vagrantfile"					, IC_VAGRANT			}, //  2371  ⍱
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
	END_OF_ICONS
};

/* —— Directory Extension Icons ———————————————————————————————————————————————————————————————————————————————————— */

/// Array of lowercase file extensions and their icons.
const Icon DIR_EXT_ICONS[] = {
	{ "bak"				, IC_BACKUP_DIR		}, // F0D0B  󰴋
	END_OF_ICONS
};

/* —— File Extension Icons ————————————————————————————————————————————————————————————————————————————————————————— */

/// Array of lowercase file extensions and their icons.
const Icon FILE_EXT_ICONS[] = {
	{ "ai"				, IC_AI				}, //  E7B4  
	{ "cr"				, IC_CR				}, //  E62F  
	{ "cu"				, IC_CU				}, //  E64B  
	{ "jl"				, IC_JL				}, //  E624  
	{ "pp"				, IC_PP				}, //  E631  
	{ "qss"				, IC_QT				}, //  F375  
	{ "qrc"				, IC_QT				}, //  F375  
	{ "qml"				, IC_QT				}, //  F375  
	{ "ui"				, IC_UI				}, //  F2D0  
	{ "vi"				, IC_VI				}, //  E81E  
	{ "acf"				, IC_ACF			}, //  F1B6  
	{ "asp"				, IC_ASP			}, //  F121  
	{ "x_t"				, IC_CAD			}, // F0EEB  󰻫
	{ "x_b"				, IC_CAD			}, // F0EEB  󰻫
	{ "stp"				, IC_CAD			}, // F0EEB  󰻫
	{ "step"			, IC_CAD			}, // F0EEB  󰻫
	{ "ste"				, IC_CAD			}, // F0EEB  󰻫
	{ "slvs"			, IC_CAD			}, // F0EEB  󰻫
	{ "sldprt"			, IC_CAD			}, // F0EEB  󰻫
	{ "sldasm"			, IC_CAD			}, // F0EEB  󰻫
	{ "skp"				, IC_CAD			}, // F0EEB  󰻫
	{ "psm"				, IC_CAD			}, // F0EEB  󰻫
	{ "ipt"				, IC_CAD			}, // F0EEB  󰻫
	{ "igs"				, IC_CAD			}, // F0EEB  󰻫
	{ "iges"			, IC_CAD			}, // F0EEB  󰻫
	{ "ige"				, IC_CAD			}, // F0EEB  󰻫
	{ "ifc"				, IC_CAD			}, // F0EEB  󰻫
	{ "iam"				, IC_CAD			}, // F0EEB  󰻫
	{ "f3z"				, IC_CAD			}, // F0EEB  󰻫
	{ "f3d"				, IC_CAD			}, // F0EEB  󰻫
	{ "dxf"				, IC_CAD			}, // F0EEB  󰻫
	{ "dwg"				, IC_CAD			}, // F0EEB  󰻫
	{ "catproduct"		, IC_CAD			}, // F0EEB  󰻫
	{ "catpart"			, IC_CAD			}, // F0EEB  󰻫
	{ "brep"			, IC_CAD			}, // F0EEB  󰻫
	{ "3dm"				, IC_CAD			}, // F0EEB  󰻫
	{ "123dx"			, IC_CAD			}, // F0EEB  󰻫
	{ "com"				, IC_COM			}, //  E629  
	{ "cow"				, IC_COW			}, // F019A  󰆚
	{ "csv"				, IC_CSV			}, //  EEFC  
	{ "deb"				, IC_DEB			}, //  E77D  
	{ "ejs"				, IC_EJS			}, //  E618  
	{ "elm"				, IC_ELM			}, //  E62C  
	{ "eml"				, IC_EML			}, //  F003  
	{ "env"				, IC_ENV			}, //  F462  
	{ "z64"				, IC_GBA			}, // F1393  󱎓
	{ "gba"				, IC_GBA			}, // F1393  󱎓
	{ "git"				, IC_GIT			}, // F02A2  󰊢
	{ "gresource"		, IC_GTK			}, //  F362  
	{ "hex"				, IC_HEX			}, // F12A7  󱊧
	{ "pfx"				, IC_KEY			}, //  EB11  
	{ "pem"				, IC_KEY			}, //  EB11  
	{ "p12"				, IC_KEY			}, //  EB11  
	{ "key"				, IC_KEY			}, //  EB11  
	{ "log"				, IC_LOG			}, //  F18D  
	{ "mid"				, IC_MID			}, // F08F2  󰣲
	{ "msf"				, IC_MSF			}, //  F370  
	{ "odf"				, IC_ODF			}, //  F37B  
	{ "odg"				, IC_ODG			}, //  F379  
	{ "fodg"			, IC_ODG			}, //  F379  
	{ "odp"				, IC_ODP			}, //  F37A  
	{ "fodp"			, IC_ODP			}, //  F37A  
	{ "ods"				, IC_ODS			}, //  F378  
	{ "fods"			, IC_ODS			}, //  F378  
	{ "odt"				, IC_ODT			}, //  F37C  
	{ "fodt"			, IC_ODT			}, //  F37C  
	{ "org"				, IC_ORG			}, //  E633  
	{ "out"				, IC_OUT			}, //  EB2C  
	{ "pdf"				, IC_PDF			}, //  F1C1  
	{ "pkg"				, IC_PKG			}, //  EB29  
	{ "rdb"				, IC_RDB			}, //  E76D  
	{ "rpm"				, IC_RPM			}, //  E7BB  
	{ "rss"				, IC_RSS			}, //  F09E  
	{ "tcl"				, IC_TCL			}, // F06D3  󰛓
	{ "tbc"				, IC_TCL			}, // F06D3  󰛓
	{ "vhs"				, IC_VHS			}, // F0A1B  󰨛
	{ "vim"				, IC_VIM			}, //  E7C5  
	{ "vue"				, IC_VUE			}, // F0844  󰡄
	{ "xul"				, IC_XML			}, // F05C0  󰗀
	{ "xml"				, IC_XML			}, // F05C0  󰗀
	{ "opml"			, IC_XML			}, // F05C0  󰗀
	{ "xpi"				, IC_XPI			}, //  EAE6  
	{ "zig"				, IC_ZIG			}, //  E6A9  
	{ "mobi"			, IC_BOOK			}, //  E28B  
	{ "epub"			, IC_BOOK			}, //  E28B  
	{ "ebook"			, IC_BOOK			}, //  E28B  
	{ "css"				, IC_CSS3			}, //  E749  
	{ "dart"			, IC_DART			}, //  E798  
	{ "patch"			, IC_DIFF			}, //  F440  
	{ "diff"			, IC_DIFF			}, //  F440  
	{ "woff2"			, IC_FONT			}, //  F031  
	{ "woff"			, IC_FONT			}, //  F031  
	{ "ttf"				, IC_FONT			}, //  F031  
	{ "ttc"				, IC_FONT			}, //  F031  
	{ "psf"				, IC_FONT			}, //  F031  
	{ "otf"				, IC_FONT			}, //  F031  
	{ "lff"				, IC_FONT			}, //  F031  
	{ "font"			, IC_FONT			}, //  F031  
	{ "fon"				, IC_FONT			}, //  F031  
	{ "fnt"				, IC_FONT			}, //  F031  
	{ "flf"				, IC_FONT			}, //  F031  
	{ "flc"				, IC_FONT			}, //  F031  
	{ "eot"				, IC_FONT			}, //  F031  
	{ "bdf"				, IC_FONT			}, //  F031  
	{ "xcf"				, IC_GIMP			}, //  F338  
	{ "haml"			, IC_HAML			}, //  E664  
	{ "nfo"				, IC_INFO			}, //  F129  
	{ "info"			, IC_INFO			}, //  F129  
	{ "webmanifest"		, IC_JSON			}, //  E60B  
	{ "properties"		, IC_JSON			}, //  E60B  
	{ "jsonc"			, IC_JSON			}, //  E60B  
	{ "json5"			, IC_JSON			}, //  E60B  
	{ "json"			, IC_JSON			}, //  E60B  
	{ "avro"			, IC_JSON			}, //  E60B  
	{ "less"			, IC_LESS			}, //  E758  
	{ "lisp"			, IC_LISP			}, // F0172  󰅲
	{ "lock"			, IC_LOCK			}, //  F023  
	{ "lck"				, IC_LOCK			}, //  F023  
	{ "mk"				, IC_MAKE			}, //  E673  
	{ "norg"			, IC_NORG			}, //  E847  
	{ "opam"			, IC_OPAM			}, // F0627  󰘧
	{ "purs"			, IC_PURS			}, //  E630  
	{ "scad"			, IC_SCAD			}, //  F34E  
	{ "txt"				, IC_TEXT			}, //  F15C  
	{ "rtf"				, IC_TEXT			}, //  F15C  
	{ "rst"				, IC_TEXT			}, //  F15C  
	{ "tmux"			, IC_TMUX			}, //  EBC8  
	{ "toml"			, IC_TOML			}, //  E6B2  
	{ "twig"			, IC_TWIG			}, //  E61C  
	{ "vala"			, IC_VALA			}, //  E8D1  
	{ "vsix"			, IC_VSIX			}, // F0A1E  󰨞
	{ "xaml"			, IC_XAML			}, // F0673  󰙳
	{ "yml"				, IC_YAML			}, //  E6A8  
	{ "yaml"			, IC_YAML			}, //  E6A8  
	{ "wv"				, IC_AUDIO			}, //  F4AE  
	{ "wma"				, IC_AUDIO			}, //  F4AE  
	{ "wav"				, IC_AUDIO			}, //  F4AE  
	{ "swf"				, IC_AUDIO			}, //  F4AE  
	{ "pcm"				, IC_AUDIO			}, //  F4AE  
	{ "opus"			, IC_AUDIO			}, //  F4AE  
	{ "ogg"				, IC_AUDIO			}, //  F4AE  
	{ "mp3"				, IC_AUDIO			}, //  F4AE  
	{ "mp2"				, IC_AUDIO			}, //  F4AE  
	{ "mka"				, IC_AUDIO			}, //  F4AE  
	{ "m4a"				, IC_AUDIO			}, //  F4AE  
	{ "flac"			, IC_AUDIO			}, //  F4AE  
	{ "ape"				, IC_AUDIO			}, //  F4AE  
	{ "alac"			, IC_AUDIO			}, //  F4AE  
	{ "aiff"			, IC_AUDIO			}, //  F4AE  
	{ "aifc"			, IC_AUDIO			}, //  F4AE  
	{ "aif"				, IC_AUDIO			}, //  F4AE  
	{ "aac"				, IC_AUDIO			}, //  F4AE  
	{ "blend"			, IC_BLEND			}, // F00AB  󰂫
	{ "cache"			, IC_CACHE			}, //  F49B  
	{ "cmake"			, IC_CMAKE			}, //  E794  
	{ "conda"			, IC_CONDA			}, //  E715  
	{ "elc"				, IC_EMACS			}, //  E632  
	{ "el"				, IC_EMACS			}, //  E632  
	{ "nix"				, IC_FLAKE			}, //  F313  
	{ "gcode"			, IC_GCODE			}, // F0AF4  󰫴
	{ "gform"			, IC_GFORM			}, //  F298  
	{ "tscn"			, IC_GODOT			}, //  E65F  
	{ "tres"			, IC_GODOT			}, //  E65F  
	{ "godot"			, IC_GODOT			}, //  E65F  
	{ "gd"				, IC_GODOT			}, //  E65F  
	{ "gv"				, IC_GRAPH			}, // F1049  󱁉
	{ "dot"				, IC_GRAPH			}, // F1049  󱁉
	{ "xhtml"			, IC_HTML5			}, //  F13B  
	{ "shtml"			, IC_HTML5			}, //  F13B  
	{ "html"			, IC_HTML5			}, //  F13B  
	{ "htm"				, IC_HTML5			}, //  F13B  
	{ "xpm"				, IC_IMAGE			}, //  F1C5  
	{ "webp"			, IC_IMAGE			}, //  F1C5  
	{ "tiff"			, IC_IMAGE			}, //  F1C5  
	{ "tif"				, IC_IMAGE			}, //  F1C5  
	{ "raw"				, IC_IMAGE			}, //  F1C5  
	{ "pxm"				, IC_IMAGE			}, //  F1C5  
	{ "ppm"				, IC_IMAGE			}, //  F1C5  
	{ "pnm"				, IC_IMAGE			}, //  F1C5  
	{ "png"				, IC_IMAGE			}, //  F1C5  
	{ "pgm"				, IC_IMAGE			}, //  F1C5  
	{ "pbm"				, IC_IMAGE			}, //  F1C5  
	{ "orf"				, IC_IMAGE			}, //  F1C5  
	{ "nef"				, IC_IMAGE			}, //  F1C5  
	{ "jxl"				, IC_IMAGE			}, //  F1C5  
	{ "jpx"				, IC_IMAGE			}, //  F1C5  
	{ "jpg"				, IC_IMAGE			}, //  F1C5  
	{ "jpf"				, IC_IMAGE			}, //  F1C5  
	{ "jpeg"			, IC_IMAGE			}, //  F1C5  
	{ "jpe"				, IC_IMAGE			}, //  F1C5  
	{ "jp2"				, IC_IMAGE			}, //  F1C5  
	{ "jif"				, IC_IMAGE			}, //  F1C5  
	{ "jfif"			, IC_IMAGE			}, //  F1C5  
	{ "jfi"				, IC_IMAGE			}, //  F1C5  
	{ "j2k"				, IC_IMAGE			}, //  F1C5  
	{ "j2c"				, IC_IMAGE			}, //  F1C5  
	{ "ico"				, IC_IMAGE			}, //  F1C5  
	{ "heif"			, IC_IMAGE			}, //  F1C5  
	{ "heic"			, IC_IMAGE			}, //  F1C5  
	{ "gif"				, IC_IMAGE			}, //  F1C5  
	{ "dvi"				, IC_IMAGE			}, //  F1C5  
	{ "cr2"				, IC_IMAGE			}, //  F1C5  
	{ "cbz"				, IC_IMAGE			}, //  F1C5  
	{ "cbr"				, IC_IMAGE			}, //  F1C5  
	{ "bmp"				, IC_IMAGE			}, //  F1C5  
	{ "avif"			, IC_IMAGE			}, //  F1C5  
	{ "arw"				, IC_IMAGE			}, //  F1C5  
	{ "jwmrc"			, IC_JWMRC			}, //  F35B  
	{ "kicad_wks"		, IC_KICAD			}, //  F34C  
	{ "kicad_sym"		, IC_KICAD			}, //  F34C  
	{ "kicad_sch"		, IC_KICAD			}, //  F34C  
	{ "kicad_pro"		, IC_KICAD			}, //  F34C  
	{ "kicad_prl"		, IC_KICAD			}, //  F34C  
	{ "kicad_pcb"		, IC_KICAD			}, //  F34C  
	{ "kicad_mod"		, IC_KICAD			}, //  F34C  
	{ "kicad_dru"		, IC_KICAD			}, //  F34C  
	{ "krz"				, IC_KRITA			}, //  F33D  
	{ "kra"				, IC_KRITA			}, //  F33D  
	{ "kpp"				, IC_KRITA			}, //  F33D  
	{ "ninja"			, IC_NINJA			}, // F0774  󰝴
	{ "razor"			, IC_RAZOR			}, //  F1FA  
	{ "cshtml"			, IC_RAZOR			}, //  F1FA  
	{ "tsx"				, IC_REACT			}, //  E7BA  
	{ "jsx"				, IC_REACT			}, //  E7BA  
	{ "scala"			, IC_SCALA			}, //  E737  
	{ "xlsx"			, IC_SHEET			}, //  F1C3  
	{ "xlsm"			, IC_SHEET			}, //  F1C3  
	{ "xls"				, IC_SHEET			}, //  F1C3  
	{ "xlr"				, IC_SHEET			}, //  F1C3  
	{ "tsv"				, IC_SHEET			}, //  F1C3  
	{ "gsheet"			, IC_SHEET			}, //  F1C3  
	{ "zsh-theme"		, IC_SHELL			}, // F1183  󱆃
	{ "pptx"			, IC_SLIDE			}, //  F1C4  
	{ "ppt"				, IC_SLIDE			}, //  F1C4  
	{ "ppsx"			, IC_SLIDE			}, //  F1C4  
	{ "pps"				, IC_SLIDE			}, //  F1C4  
	{ "gslides"			, IC_SLIDE			}, //  F1C4  
	{ "xcplayground"	, IC_SWIFT			}, //  E755  
	{ "swift"			, IC_SWIFT			}, //  E755  
	{ "typ"				, IC_TYPST			}, //  F37F  
	{ "unity3d"			, IC_UNITY			}, //  E721  
	{ "unity"			, IC_UNITY			}, //  E721  
	{ "o"				, IC_BINARY			}, //  EAE8  
	{ "hi"				, IC_BINARY			}, //  EAE8  
	{ "elf"				, IC_BINARY			}, //  EAE8  
	{ "bin"				, IC_BINARY			}, //  EAE8  
	{ "app"				, IC_BINARY			}, //  EAE8  
	{ "coffee"			, IC_COFFEE			}, //  F0F4  
	{ "tml"				, IC_CONFIG			}, // F107B  󱁻
	{ "ini"				, IC_CONFIG			}, // F107B  󱁻
	{ "config"			, IC_CONFIG			}, // F107B  󱁻
	{ "conf"			, IC_CONFIG			}, // F107B  󱁻
	{ "cfg"				, IC_CONFIG			}, // F107B  󱁻
	{ "dockerignore"	, IC_DOCKER			}, //  E650  
	{ "dockerfile"		, IC_DOCKER			}, //  E650  
	{ "drawio"			, IC_DRAWIO			}, //  EBBA  
	{ "ebuild"			, IC_EBUILD			}, //  F30D  
	{ "hrl"				, IC_ERLANG			}, //  E7B1  
	{ "erl"				, IC_ERLANG			}, //  E7B1  
	{ "gradle"			, IC_GRADLE			}, //  E660  
	{ "m"				, IC_LANG_C			}, //  E61E  
	{ "inl"				, IC_LANG_C			}, //  E61E  
	{ "h"				, IC_LANG_C			}, //  E61E  
	{ "c"				, IC_LANG_C			}, //  E61E  
	{ "di"				, IC_LANG_D			}, //  E7AF  
	{ "d"				, IC_LANG_D			}, //  E7AF  
	{ "rds"				, IC_LANG_R			}, //  E68A  
	{ "rdata"			, IC_LANG_R			}, //  E68A  
	{ "r"				, IC_LANG_R			}, //  E68A  
	{ "v"				, IC_LANG_V			}, //  E6AC  
	{ "magnet"			, IC_MAGNET			}, //  F076  
	{ "node"			, IC_NODEJS			}, //  E718  
	{ "readme"			, IC_README			}, // F00BA  󰂺
	{ "sqlite3"			, IC_SQLITE			}, //  E7C4  
	{ "sqlite"			, IC_SQLITE			}, //  E7C4  
	{ "sl3"				, IC_SQLITE			}, //  E7C4  
	{ "s3db"			, IC_SQLITE			}, //  E7C4  
	{ "db3"				, IC_SQLITE			}, //  E7C4  
	{ "svelte"			, IC_SVELTE			}, //  E697  
	{ "xci"				, IC_SWITCH			}, // F07E1  󰟡
	{ "nsp"				, IC_SWITCH			}, // F07E1  󰟡
	{ "svg"				, IC_VECTOR			}, // F0559  󰕙
	{ "ps"				, IC_VECTOR			}, // F0559  󰕙
	{ "eps"				, IC_VECTOR			}, // F0559  󰕙
	{ "wmv"				, IC_VIDEOS			}, //  F03D  
	{ "webm"			, IC_VIDEOS			}, //  F03D  
	{ "vob"				, IC_VIDEOS			}, //  F03D  
	{ "video"			, IC_VIDEOS			}, //  F03D  
	{ "ogv"				, IC_VIDEOS			}, //  F03D  
	{ "ogm"				, IC_VIDEOS			}, //  F03D  
	{ "mpg"				, IC_VIDEOS			}, //  F03D  
	{ "mpeg"			, IC_VIDEOS			}, //  F03D  
	{ "mp4"				, IC_VIDEOS			}, //  F03D  
	{ "mov"				, IC_VIDEOS			}, //  F03D  
	{ "mkv"				, IC_VIDEOS			}, //  F03D  
	{ "m4v"				, IC_VIDEOS			}, //  F03D  
	{ "m2v"				, IC_VIDEOS			}, //  F03D  
	{ "m2ts"			, IC_VIDEOS			}, //  F03D  
	{ "heics"			, IC_VIDEOS			}, //  F03D  
	{ "h264"			, IC_VIDEOS			}, //  F03D  
	{ "flv"				, IC_VIDEOS			}, //  F03D  
	{ "cast"			, IC_VIDEOS			}, //  F03D  
	{ "avi"				, IC_VIDEOS			}, //  F03D  
	{ "3gpp2"			, IC_VIDEOS			}, //  F03D  
	{ "3gpp"			, IC_VIDEOS			}, //  F03D  
	{ "3gp2"			, IC_VIDEOS			}, //  F03D  
	{ "3gp"				, IC_VIDEOS			}, //  F03D  
	{ "3g2"				, IC_VIDEOS			}, //  F03D  
	{ "suo"				, IC_VSCODE			}, //  E70C  
	{ "sln"				, IC_VSCODE			}, //  E70C  
	{ "prjpcb"			, IC_EDA_PCB		}, //  EABE  
	{ "pcbdoc"			, IC_EDA_PCB		}, //  EABE  
	{ "lpp"				, IC_EDA_PCB		}, //  EABE  
	{ "gts"				, IC_EDA_PCB		}, //  EABE  
	{ "gtp"				, IC_EDA_PCB		}, //  EABE  
	{ "gto"				, IC_EDA_PCB		}, //  EABE  
	{ "gtl"				, IC_EDA_PCB		}, //  EABE  
	{ "gml"				, IC_EDA_PCB		}, //  EABE  
	{ "gm1"				, IC_EDA_PCB		}, //  EABE  
	{ "gbs"				, IC_EDA_PCB		}, //  EABE  
	{ "gbr"				, IC_EDA_PCB		}, //  EABE  
	{ "gbp"				, IC_EDA_PCB		}, //  EABE  
	{ "gbo"				, IC_EDA_PCB		}, //  EABE  
	{ "gbl"				, IC_EDA_PCB		}, //  EABE  
	{ "brd"				, IC_EDA_PCB		}, //  EABE  
	{ "schdoc"			, IC_EDA_SCH		}, // F0B45  󰭅
	{ "sch"				, IC_EDA_SCH		}, // F0B45  󰭅
	{ "wrz"				, IC_FILE_3D		}, // F01A7  󰆧
	{ "wrl"				, IC_FILE_3D		}, // F01A7  󰆧
	{ "stl"				, IC_FILE_3D		}, // F01A7  󰆧
	{ "ply"				, IC_FILE_3D		}, // F01A7  󰆧
	{ "obj"				, IC_FILE_3D		}, // F01A7  󰆧
	{ "fbx"				, IC_FILE_3D		}, // F01A7  󰆧
	{ "3mf"				, IC_FILE_3D		}, // F01A7  󰆧
	{ "fctl"			, IC_FREECAD		}, //  F336  
	{ "fctb"			, IC_FREECAD		}, //  F336  
	{ "fcstd1"			, IC_FREECAD		}, //  F336  
	{ "fcstd"			, IC_FREECAD		}, //  F336  
	{ "fcscript"		, IC_FREECAD		}, //  F336  
	{ "fcparam"			, IC_FREECAD		}, //  F336  
	{ "fcmat"			, IC_FREECAD		}, //  F336  
	{ "fcmacro"			, IC_FREECAD		}, //  F336  
	{ "fcbak"			, IC_FREECAD		}, //  F336  
	{ "graphql"			, IC_GRAPHQL		}, //  E662  
	{ "gql"				, IC_GRAPHQL		}, //  E662  
	{ "kdbx"			, IC_KEYPASS		}, //  F23E  
	{ "kdb"				, IC_KEYPASS		}, //  F23E  
	{ "go"				, IC_LANG_GO		}, //  E65E  
	{ "lib"				, IC_LIBRARY		}, //  EB9C  
	{ "lbr"				, IC_LIBRARY		}, //  EB9C  
	{ "dll"				, IC_LIBRARY		}, //  EB9C  
	{ "license"			, IC_LICENSE		}, //  F02D  
	{ "service"			, IC_SERVICE		}, //  EBA2  
	{ "sr"				, IC_SQ_WAVE		}, // F147B  󱑻
	{ "sal"				, IC_SQ_WAVE		}, // F147B  󱑻
	{ "sublime-theme"	, IC_SUBLIME		}, //  E7AA  
	{ "sublime-snippet"	, IC_SUBLIME		}, //  E7AA  
	{ "sublime-settings", IC_SUBLIME		}, //  E7AA  
	{ "sublime-session"	, IC_SUBLIME		}, //  E7AA  
	{ "sublime-project"	, IC_SUBLIME		}, //  E7AA  
	{ "sublime-package"	, IC_SUBLIME		}, //  E7AA  
	{ "sublime-options"	, IC_SUBLIME		}, //  E7AA  
	{ "sublime-menu"	, IC_SUBLIME		}, //  E7AA  
	{ "sublime-keymap"	, IC_SUBLIME		}, //  E7AA  
	{ "sublime-build"	, IC_SUBLIME		}, //  E7AA  
	{ "torrent"			, IC_TORRENT		}, //  E275  
	{ "ifb"				, IC_CALENDAR		}, //  EAB0  
	{ "ics"				, IC_CALENDAR		}, //  EAB0  
	{ "icalendar"		, IC_CALENDAR		}, //  EAB0  
	{ "ical"			, IC_CALENDAR		}, //  EAB0  
	{ "sql"				, IC_DATABASE		}, //  F1C0  
	{ "prql"			, IC_DATABASE		}, //  F1C0  
	{ "odb"				, IC_DATABASE		}, //  F1C0  
	{ "mdb"				, IC_DATABASE		}, //  F1C0  
	{ "ldb"				, IC_DATABASE		}, //  F1C0  
	{ "dump"			, IC_DATABASE		}, //  F1C0  
	{ "dconf"			, IC_DATABASE		}, //  F1C0  
	{ "db"				, IC_DATABASE		}, //  F1C0  
	{ "gdoc"			, IC_DOCUMENT		}, //  F1C2  
	{ "docx"			, IC_DOCUMENT		}, //  F1C2  
	{ "docm"			, IC_DOCUMENT		}, //  F1C2  
	{ "doc"				, IC_DOCUMENT		}, //  F1C2  
	{ "djvu"			, IC_DOCUMENT		}, //  F1C2  
	{ "djv"				, IC_DOCUMENT		}, //  F1C2  
	{ "part"			, IC_DOWNLOAD		}, // F01DA  󰇚
	{ "fdmdownload"		, IC_DOWNLOAD		}, // F01DA  󰇚
	{ "download"		, IC_DOWNLOAD		}, // F01DA  󰇚
	{ "crdownload"		, IC_DOWNLOAD		}, // F01DA  󰇚
	{ "iml"				, IC_INTELLIJ		}, //  E7B5  
	{ "kdenlivetitle"	, IC_KDENLIVE		}, //  F33C  
	{ "kdenlive"		, IC_KDENLIVE		}, //  F33C  
	{ "mm"				, IC_LANG_CPP		}, //  E61D  
	{ "hxx"				, IC_LANG_CPP		}, //  E61D  
	{ "hpp"				, IC_LANG_CPP		}, //  E61D  
	{ "hh"				, IC_LANG_CPP		}, //  E61D  
	{ "h++"				, IC_LANG_CPP		}, //  E61D  
	{ "cxx"				, IC_LANG_CPP		}, //  E61D  
	{ "cpp"				, IC_LANG_CPP		}, //  E61D  
	{ "cp"				, IC_LANG_CPP		}, //  E61D  
	{ "cc"				, IC_LANG_CPP		}, //  E61D  
	{ "c++"				, IC_LANG_CPP		}, //  E61D  
	{ "vhdl"			, IC_LANG_HDL		}, // F035B  󰍛
	{ "svh"				, IC_LANG_HDL		}, // F035B  󰍛
	{ "sv"				, IC_LANG_HDL		}, // F035B  󰍛
	{ "luau"			, IC_LANG_LUA		}, //  E620  
	{ "luac"			, IC_LANG_LUA		}, //  E620  
	{ "lua"				, IC_LANG_LUA		}, //  E620  
	{ "nims"			, IC_LANG_NIM		}, //  E677  
	{ "nimble"			, IC_LANG_NIM		}, //  E677  
	{ "nim"				, IC_LANG_NIM		}, //  E677  
	{ "php"				, IC_LANG_PHP		}, //  E73D  
	{ "phar"			, IC_LANG_PHP		}, //  E73D  
	{ "tex"				, IC_LANG_TEX		}, //  E69B  
	{ "sty"				, IC_LANG_TEX		}, //  E69B  
	{ "ltx"				, IC_LANG_TEX		}, //  E69B  
	{ "latex"			, IC_LANG_TEX		}, //  E69B  
	{ "cls"				, IC_LANG_TEX		}, //  E69B  
	{ "bst"				, IC_LANG_TEX		}, //  E69B  
	{ "bib"				, IC_LANG_TEX		}, //  E69B  
	{ "rmd"				, IC_MARKDOWN		}, //  E68B  
	{ "rdoc"			, IC_MARKDOWN		}, //  F48A  
	{ "mkd"				, IC_MARKDOWN		}, //  F48A  
	{ "mdx"				, IC_MARKDOWN		}, //  F48A  
	{ "md"				, IC_MARKDOWN		}, //  F48A  
	{ "markdown"		, IC_MARKDOWN		}, //  F48A  
	{ "jmd"				, IC_MARKDOWN		}, //  F48A  
	{ "mustache"		, IC_MUSTACHE		}, //  E60F  
	{ "hbs"				, IC_MUSTACHE		}, //  E60F  
	{ "ipynb"			, IC_NOTEBOOK		}, //  E678  
	{ "plist"			, IC_OS_APPLE		}, //  F179  
	{ "localized"		, IC_OS_APPLE		}, //  F179  
	{ "dylib"			, IC_OS_APPLE		}, //  F179  
	{ "bundle"			, IC_OS_APPLE		}, //  F179  
	{ "applescript"		, IC_OS_APPLE		}, //  F179  
	{ "apple"			, IC_OS_APPLE		}, //  F179  
	{ "so"				, IC_OS_LINUX		}, //  F17C  
	{ "ko"				, IC_OS_LINUX		}, //  F17C  
	{ "a"				, IC_OS_LINUX		}, //  F17C  
	{ "pls"				, IC_PLAYLIST		}, // F0CB9  󰲹
	{ "m3u8"			, IC_PLAYLIST		}, // F0CB9  󰲹
	{ "m3u"				, IC_PLAYLIST		}, // F0CB9  󰲹
	{ "cue"				, IC_PLAYLIST		}, // F0CB9  󰲹
	{ "sub"				, IC_SUBTITLE		}, // F0A16  󰨖
	{ "ssa"				, IC_SUBTITLE		}, // F0A16  󰨖
	{ "srt"				, IC_SUBTITLE		}, // F0A16  󰨖
	{ "sbt"				, IC_SUBTITLE		}, // F0A16  󰨖
	{ "lrc"				, IC_SUBTITLE		}, // F0A16  󰨖
	{ "ass"				, IC_SUBTITLE		}, // F0A16  󰨖
	{ "cljc"			, IC_CLOJURE_1		}, //  E768  
	{ "clj"				, IC_CLOJURE_1		}, //  E768  
	{ "edn"				, IC_CLOJURE_2		}, //  E76A  
	{ "cljs"			, IC_CLOJURE_2		}, //  E76A  
	{ "war"				, IC_LANG_JAVA		}, //  E256  
	{ "java"			, IC_LANG_JAVA		}, //  E256  
	{ "jar"				, IC_LANG_JAVA		}, //  E256  
	{ "jad"				, IC_LANG_JAVA		}, //  E256  
	{ "class"			, IC_LANG_JAVA		}, //  E256  
	{ "t"				, IC_LANG_PERL		}, //  E67E  
	{ "pod"				, IC_LANG_PERL		}, //  E67E  
	{ "pm"				, IC_LANG_PERL		}, //  E67E  
	{ "plx"				, IC_LANG_PERL		}, //  E67E  
	{ "pl"				, IC_LANG_PERL		}, //  E67E  
	{ "ru"				, IC_LANG_RUBY		}, //  E739  
	{ "rspec_status"	, IC_LANG_RUBY		}, //  E739  
	{ "rspec_parallel"	, IC_LANG_RUBY		}, //  E739  
	{ "rspec"			, IC_LANG_RUBY		}, //  E739  
	{ "rb"				, IC_LANG_RUBY		}, //  E739  
	{ "rakefile"		, IC_LANG_RUBY		}, //  E739  
	{ "rake"			, IC_LANG_RUBY		}, //  E739  
	{ "procfile"		, IC_LANG_RUBY		}, //  E739  
	{ "guardfile"		, IC_LANG_RUBY		}, //  E739  
	{ "gemspec"			, IC_LANG_RUBY		}, //  E739  
	{ "gemfile"			, IC_LANG_RUBY		}, //  E739  
	{ "gem"				, IC_LANG_RUBY		}, //  E739  
	{ "rs"				, IC_LANG_RUST		}, //  E68B  
	{ "rmeta"			, IC_LANG_RUST		}, //  E68B  
	{ "rlib"			, IC_LANG_RUST		}, //  E68B  
	{ "scss"			, IC_LANG_SASS		}, //  E603  
	{ "sass"			, IC_LANG_SASS		}, //  E603  
	{ "psd"				, IC_PHOTOSHOP		}, //  E7B8  
	{ "psb"				, IC_PHOTOSHOP		}, //  E7B8  
	{ "zsh"				, IC_SHELL_CMD		}, //  F489  
	{ "shell"			, IC_SHELL_CMD		}, //  F489  
	{ "sh"				, IC_SHELL_CMD		}, //  F489  
	{ "nu"				, IC_SHELL_CMD		}, //  F489  
	{ "ksh"				, IC_SHELL_CMD		}, //  F489  
	{ "fish"			, IC_SHELL_CMD		}, //  F489  
	{ "csh"				, IC_SHELL_CMD		}, //  F489  
	{ "bats"			, IC_SHELL_CMD		}, //  F489  
	{ "bash"			, IC_SHELL_CMD		}, //  F489  
	{ "awk"				, IC_SHELL_CMD		}, //  F489  
	{ "tfvars"			, IC_TERRAFORM		}, // F1062  󱁢
	{ "tfstate"			, IC_TERRAFORM		}, // F1062  󱁢
	{ "tf"				, IC_TERRAFORM		}, // F1062  󱁢
	{ "sfz"				, IC_TREB_CLEF		}, // F0F70  󰽰
	{ "sf2"				, IC_TREB_CLEF		}, // F0F70  󰽰
	{ "zst"				, IC_COMPRESSED		}, //  F410  
	{ "zip"				, IC_COMPRESSED		}, //  F410  
	{ "z"				, IC_COMPRESSED		}, //  F410  
	{ "xz"				, IC_COMPRESSED		}, //  F410  
	{ "tzo"				, IC_COMPRESSED		}, //  F410  
	{ "tz"				, IC_COMPRESSED		}, //  F410  
	{ "txz"				, IC_COMPRESSED		}, //  F410  
	{ "tlz"				, IC_COMPRESSED		}, //  F410  
	{ "tgz"				, IC_COMPRESSED		}, //  F410  
	{ "tbz2"			, IC_COMPRESSED		}, //  F410  
	{ "tbz"				, IC_COMPRESSED		}, //  F410  
	{ "taz"				, IC_COMPRESSED		}, //  F410  
	{ "tar"				, IC_COMPRESSED		}, //  F410  
	{ "rar"				, IC_COMPRESSED		}, //  F410  
	{ "par"				, IC_COMPRESSED		}, //  F410  
	{ "lzo"				, IC_COMPRESSED		}, //  F410  
	{ "lzma"			, IC_COMPRESSED		}, //  F410  
	{ "lzh"				, IC_COMPRESSED		}, //  F410  
	{ "lz4"				, IC_COMPRESSED		}, //  F410  
	{ "lz"				, IC_COMPRESSED		}, //  F410  
	{ "gz"				, IC_COMPRESSED		}, //  F410  
	{ "cpio"			, IC_COMPRESSED		}, //  F410  
	{ "bz3"				, IC_COMPRESSED		}, //  F410  
	{ "bz2"				, IC_COMPRESSED		}, //  F410  
	{ "bz"				, IC_COMPRESSED		}, //  F410  
	{ "br"				, IC_COMPRESSED		}, //  F410  
	{ "arj"				, IC_COMPRESSED		}, //  F410  
	{ "ar"				, IC_COMPRESSED		}, //  F410  
	{ "7z"				, IC_COMPRESSED		}, //  F410  
	{ "vmdk"			, IC_DISK_IMAGE		}, //  E271  
	{ "vhd"				, IC_DISK_IMAGE		}, //  E271  
	{ "vdi"				, IC_DISK_IMAGE		}, //  E271  
	{ "tc"				, IC_DISK_IMAGE		}, //  E271  
	{ "qcow2"			, IC_DISK_IMAGE		}, //  E271  
	{ "qcow"			, IC_DISK_IMAGE		}, //  E271  
	{ "iso"				, IC_DISK_IMAGE		}, //  E271  
	{ "img"				, IC_DISK_IMAGE		}, //  E271  
	{ "image"			, IC_DISK_IMAGE		}, //  E271  
	{ "dmg"				, IC_DISK_IMAGE		}, //  E271  
	{ "gleam"			, IC_LANG_GLEAM		}, // F09A5  󰦥
	{ "hc"				, IC_LANG_HOLYC		}, // F00A2  󰂢
	{ "mjs"				, IC_LANG_JSCPT		}, //  E74E  
	{ "js"				, IC_LANG_JSCPT		}, //  E74E  
	{ "cjs"				, IC_LANG_JSCPT		}, //  E74E  
	{ "mly"				, IC_LANG_OCAML		}, //  E67A  
	{ "mll"				, IC_LANG_OCAML		}, //  E67A  
	{ "mli"				, IC_LANG_OCAML		}, //  E67A  
	{ "ml"				, IC_LANG_OCAML		}, //  E67A  
	{ "ts"				, IC_LANG_TSCPT		}, //  E628  
	{ "mts"				, IC_LANG_TSCPT		}, //  E628  
	{ "cts"				, IC_LANG_TSCPT		}, //  E628  
	{ "apk"				, IC_OS_ANDROID		}, //  E70E  
	{ "android"			, IC_OS_ANDROID		}, //  E70E  
	{ "windows"			, IC_OS_WINDOWS		}, //  F17A  
	{ "msi"				, IC_OS_WINDOWS		}, //  F17A  
	{ "cmd"				, IC_OS_WINDOWS		}, //  F17A  
	{ "cab"				, IC_OS_WINDOWS		}, //  F17A  
	{ "psm1"			, IC_POWERSHELL		}, //  EBC7  
	{ "psd1"			, IC_POWERSHELL		}, //  EBC7  
	{ "ps1"				, IC_POWERSHELL		}, //  EBC7  
	{ "pub"				, IC_PUBLIC_KEY		}, // F0DD6  󰷖
	{ "kbx"				, IC_SHIELD_KEY		}, // F0BC4  󰯄
	{ "desktop"			, IC_DESKTOP_EXT	}, //  EBD1  
	{ "crt"				, IC_GIST_SECRET	}, //  EAFA  
	{ "cert"			, IC_GIST_SECRET	}, //  EAFA  
	{ "csx"				, IC_LANG_CSHARP	}, // F031B  󰌛
	{ "csproj"			, IC_LANG_CSHARP	}, // F031B  󰌛
	{ "cs"				, IC_LANG_CSHARP	}, // F031B  󰌛
	{ "leex"			, IC_LANG_ELIXIR	}, //  E62D  
	{ "exs"				, IC_LANG_ELIXIR	}, //  E62D  
	{ "ex"				, IC_LANG_ELIXIR	}, //  E62D  
	{ "eex"				, IC_LANG_ELIXIR	}, //  E62D  
	{ "fnl"				, IC_LANG_FENNEL	}, //  E6AF  
	{ "fsx"				, IC_LANG_FSHARP	}, //  E7A7  
	{ "fsscript"		, IC_LANG_FSHARP	}, //  E7A7  
	{ "fsproj"			, IC_LANG_FSHARP	}, //  E7A7  
	{ "fsi"				, IC_LANG_FSHARP	}, //  E7A7  
	{ "fs"				, IC_LANG_FSHARP	}, //  E7A7  
	{ "f#"				, IC_LANG_FSHARP	}, //  E7A7  
	{ "gvy"				, IC_LANG_GROOVY	}, //  E775  
	{ "groovy"			, IC_LANG_GROOVY	}, //  E775  
	{ "kts"				, IC_LANG_KOTLIN	}, //  E634  
	{ "kt"				, IC_LANG_KOTLIN	}, //  E634  
	{ "whl"				, IC_LANG_PYTHON	}, //  E606  
	{ "pyx"				, IC_LANG_PYTHON	}, //  E606  
	{ "pyw"				, IC_LANG_PYTHON	}, //  E606  
	{ "pyo"				, IC_LANG_PYTHON	}, //  E606  
	{ "pyi"				, IC_LANG_PYTHON	}, //  E606  
	{ "pyd"				, IC_LANG_PYTHON	}, //  E606  
	{ "pyc"				, IC_LANG_PYTHON	}, //  E606  
	{ "py"				, IC_LANG_PYTHON	}, //  E606  
	{ "pxd"				, IC_LANG_PYTHON	}, //  E606  
	{ "ss"				, IC_LANG_SCHEME	}, //  E6B1  
	{ "sld"				, IC_LANG_SCHEME	}, //  E6B1  
	{ "scm"				, IC_LANG_SCHEME	}, //  E6B1  
	{ "rkt"				, IC_LANG_SCHEME	}, //  E6B1  
	{ "stylus"			, IC_LANG_STYLUS	}, //  E600  
	{ "styl"			, IC_LANG_STYLUS	}, //  E600  
	{ "gpg"				, IC_SHIELD_LOCK	}, // F099D  󰦝
	{ "asc"				, IC_SHIELD_LOCK	}, // F099D  󰦝
	{ "age"				, IC_SHIELD_LOCK	}, // F099D  󰦝
	{ "signature"		, IC_SIGNED_FILE	}, // F19C3  󱧃
	{ "sig"				, IC_SIGNED_FILE	}, // F19C3  󱧃
	{ "qm"				, IC_TRANSLATION	}, // F05CA  󰗊
	{ "pot"				, IC_TRANSLATION	}, // F05CA  󰗊
	{ "po"				, IC_TRANSLATION	}, // F05CA  󰗊
	{ "mo"				, IC_TRANSLATION	}, // F05CA  󰗊
	{ "editorconfig"	, IC_EDITORCONFIG	}, //  E652  
	{ "ino"				, IC_LANG_ARDUINO	}, //  F34B  
	{ "for"				, IC_LANG_FORTRAN	}, // F121A  󱈚
	{ "f90"				, IC_LANG_FORTRAN	}, // F121A  󱈚
	{ "f"				, IC_LANG_FORTRAN	}, // F121A  󱈚
	{ "lhs"				, IC_LANG_HASKELL	}, //  E777  
	{ "hs"				, IC_LANG_HASKELL	}, //  E777  
	{ "slim"			, IC_LANG_RBRAILS	}, //  E73B  
	{ "rubydoc"			, IC_LANG_RBRAILS	}, //  E73B  
	{ "erb"				, IC_LANG_RBRAILS	}, //  E73B  
	{ "sha512"			, IC_SHIELD_CHECK	}, // F0565  󰕥
	{ "sha384"			, IC_SHIELD_CHECK	}, // F0565  󰕥
	{ "sha256"			, IC_SHIELD_CHECK	}, // F0565  󰕥
	{ "sha224"			, IC_SHIELD_CHECK	}, // F0565  󰕥
	{ "sha1"			, IC_SHIELD_CHECK	}, // F0565  󰕥
	{ "md5"				, IC_SHIELD_CHECK	}, // F0565  󰕥
	{ "s"				, IC_LANG_ASSEMBLY	}, //  E637  
	{ "asm"				, IC_LANG_ASSEMBLY	}, //  E637  
	{ "exe"				, IC_OS_WINDOWS_CMD	}, //  EBC4  
	{ "bat"				, IC_OS_WINDOWS_CMD	}, //  EBC4  
	END_OF_ICONS
};

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignoreRegexp /((?<=\bIC_)\w+|\b[0-9A-F]{4,5})\b|(?<=\{[ \t]+")[\w-.]+(?=")/g
