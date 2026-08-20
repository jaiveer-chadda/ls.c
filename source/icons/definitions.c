/// @file icons/definitions.c

#include "icons.h"

/* —— Base Icon Definitions ———————————————————————————————————————————————————————————————————————————————————————— */

#define IC_FILE				L'' /* [ • • • ] */
#define IC_FILE_UNKNOWN		L'󰡯' /* [ • • • ] */

#define IC_FOLDER			L'' /* [ • • • ] */
#define IC_FOLDER_OPEN		L'' /* [ • • • ] */

#define IC_ACF				L'' /* [ • • E ] */
#define IC_AI				L'' /* [ • • E ] */
#define IC_ARCHBTW			L'' /* [ • F • ] */
#define IC_ASP				L'' /* [ • • E ] */
#define IC_ATOM				L'' /* [ • F • ] */
#define IC_AUDIO			L'' /* [ • • E ] */
#define IC_BINARY			L'' /* [ D • E ] — JV */
#define IC_BLEND			L'󰂫' /* [ • • E ] */
#define IC_BOOK				L'' /* [ • • E ] */
#define IC_BSPWM			L'' /* [ • F • ] */
#define IC_BUN				L'' /* [ • F • ] */
#define IC_CACHE			L'' /* [ • • E ] */
#define IC_CAD				L'󰻫' /* [ • • E ] */
#define IC_CALENDAR			L'' /* [ • • E ] */
#define IC_CLOCK			L'' /* [ • F • ] */
#define IC_CLOJURE_1		L'' /* [ • • E ] */
#define IC_CLOJURE_2		L'' /* [ • • E ] */
#define IC_CMAKE			L'' /* [ • F E ] */
#define IC_CODE_OF_CONDUCT	L'' /* [ • F • ] */
#define IC_CODESPELL		L'󰓆' /* [ • F • ] */
#define IC_COFFEE			L'' /* [ • • E ] */
#define IC_COM				L'' /* [ • • E ] */
#define IC_COMPRESSED		L'' /* [ • • E ] */
#define IC_CONDA			L'' /* [ • F E ] */
#define IC_CONFIG			L'󱁻' /* [ • F E ] */
#define IC_CONTACTS			L'󰉌' /* [ D • • ] */
#define IC_COW				L'󰆚' /* [ • • E ] */
#define IC_CR				L'' /* [ • • E ] */
#define IC_CSS3				L'' /* [ • • E ] */
#define IC_CSV				L'' /* [ • • E ] */
#define IC_CU				L'' /* [ • • E ] */
#define IC_DART				L'' /* [ • • E ] */
#define IC_DATABASE			L'' /* [ • • E ] */
#define IC_DEB				L'' /* [ • • E ] */
#define IC_DESKTOP			L'' /* [ D • • ] */
#define IC_DESKTOP_EXT		L'' /* [ • • E ] */
#define IC_DIFF				L'' /* [ • • E ] */
#define IC_DISK_IMAGE		L'' /* [ • • E ] */
#define IC_DOCKER			L'' /* [ • F E ] */
#define IC_DOCUMENT			L'' /* [ • • E ] */
#define IC_DOCUMENTS		L'󰲂' /* [ D • • ] */
#define IC_DOWNLOAD			L'󰇚' /* [ • • E ] */
#define IC_DOWNLOADS		L'󰉍' /* [ D • • ] */
#define IC_DRAWIO			L'' /* [ • • E ] */
#define IC_DROPBOX			L'' /* [ • F • ] */
#define IC_EARTH			L'' /* [ • F • ] */
#define IC_EBUILD			L'' /* [ • • E ] */
#define IC_EDA_PCB			L'' /* [ • • E ] */
#define IC_EDA_SCH			L'󰭅' /* [ • • E ] */
#define IC_EDITORCONFIG		L'' /* [ • F E ] */
#define IC_EJS				L'' /* [ • • E ] */
#define IC_ELM				L'' /* [ • • E ] */
#define IC_EMACS			L'' /* [ • F E ] */
#define IC_EML				L'' /* [ • • E ] */
#define IC_ENV				L'' /* [ • F E ] */
#define IC_ERLANG			L'' /* [ • • E ] */
#define IC_ESLINT			L'' /* [ • F • ] */
#define IC_EXERCISM			L'' /* [ D • • ] */
#define IC_FAVORITES		L'󰚝' /* [ D • • ] */
#define IC_FILE_3D			L'󰆧' /* [ • • E ] */
#define IC_FLAKE			L'' /* [ • F E ] */
#define IC_FOLDER_BUILD		L'󱧼' /* [ D • • ] */
#define IC_FOLDER_CONFIG	L'' /* [ D • • ] */
#define IC_FOLDER_GIT		L'' /* [ D • • ] */
#define IC_FOLDER_GITHUB	L'' /* [ D • • ] */
#define IC_FOLDER_HIDDEN	L'󱞞' /* [ D • • ] */
#define IC_FOLDER_KEY		L'󰢬' /* [ D • • ] */
#define IC_FOLDER_NPM		L'' /* [ D • • ] */
#define IC_FONT				L'' /* [ • F E ] */
#define IC_FREECAD			L'' /* [ • F E ] */
#define IC_GBA				L'󱎓' /* [ • • E ] */
#define IC_GCODE			L'󰫴' /* [ • • E ] */
#define IC_GFORM			L'' /* [ • • E ] */
#define IC_GIMP				L'' /* [ • • E ] */
#define IC_GIST_SECRET		L'' /* [ • • E ] */
#define IC_GIT				L'󰊢' /* [ • F E ] */
#define IC_GITLAB			L'' /* [ • F • ] */
#define IC_GODOT			L'' /* [ • • E ] */
#define IC_GOOGLE_CLOUD		L'󱇶' /* [ • F • ] */
#define IC_GRADLE			L'' /* [ • F E ] */
#define IC_GRAPH			L'󱁉' /* [ • • E ] */
#define IC_GRAPHQL			L'' /* [ • • E ] */
#define IC_GRUNT			L'' /* [ • F • ] */
#define IC_GTK				L'' /* [ • • E ] */
#define IC_GULP				L'' /* [ • F • ] */
#define IC_HAML				L'' /* [ • • E ] */
#define IC_HEROKU			L'' /* [ • F • ] */
#define IC_HEX				L'󱊧' /* [ • • E ] */
#define IC_HOME				L'󱂵' /* [ D • • ] */
#define IC_HOMEBREW			L'󱄖' /* [ • F • ] */
#define IC_HOOK				L'󰛢' /* [ • F • ] */
#define IC_HTML5			L'' /* [ • • E ] */
#define IC_HYPRLAND			L'' /* [ • F • ] */
#define IC_I3				L'' /* [ • F • ] */
#define IC_IMAGE			L'' /* [ • • E ] */
#define IC_INFO				L'' /* [ • • E ] */
#define IC_INTELLIJ			L'' /* [ • F E ] */
#define IC_JENKINSFILE		L'' /* [ • F • ] */
#define IC_JL				L'' /* [ • • E ] */
#define IC_JSON				L'' /* [ • • E ] */
#define IC_JWMRC			L'' /* [ • • E ] */
#define IC_KDE				L'' /* [ • F • ] */
#define IC_KDENLIVE			L'' /* [ • F E ] */
#define IC_KEY				L'' /* [ • • E ] */
#define IC_KEYPASS			L'' /* [ • • E ] */
#define IC_KICAD			L'' /* [ • F E ] */
#define IC_KRITA			L'' /* [ • F E ] */
#define IC_LANG_ARDUINO		L'' /* [ • • E ] */
#define IC_LANG_ASSEMBLY	L'' /* [ • • E ] */
#define IC_LANG_C			L'' /* [ • • E ] */
#define IC_LANG_CPP			L'' /* [ • • E ] */
#define IC_LANG_CSHARP		L'󰌛' /* [ • • E ] */
#define IC_LANG_D			L'' /* [ • • E ] */
#define IC_LANG_ELIXIR		L'' /* [ • F E ] */
#define IC_LANG_FENNEL		L'' /* [ • F E ] */
#define IC_LANG_FORTRAN		L'󱈚' /* [ • • E ] */
#define IC_LANG_FSHARP		L'' /* [ • • E ] */
#define IC_LANG_GLEAM		L'󰦥' /* [ • • E ] */
#define IC_LANG_GO			L'' /* [ • F E ] */
#define IC_LANG_GROOVY		L'' /* [ • • E ] */
#define IC_LANG_HASKELL		L'' /* [ D • E ] */
#define IC_LANG_HDL			L'󰍛' /* [ • • E ] */
#define IC_LANG_HOLYC		L'󰂢' /* [ • • E ] */
#define IC_LANG_JAVA		L'' /* [ • • E ] */
#define IC_LANG_JSCPT		L'' /* [ • F E ] */
#define IC_LANG_KOTLIN		L'' /* [ • • E ] */
#define IC_LANG_LUA			L'' /* [ • • E ] */
#define IC_LANG_NIM			L'' /* [ • • E ] */
#define IC_LANG_OCAML		L'' /* [ D F E ] */
#define IC_LANG_PERL		L'' /* [ • • E ] */
#define IC_LANG_PHP			L'' /* [ • F E ] */
#define IC_LANG_PYTHON		L'' /* [ • F E ] */
#define IC_LANG_R			L'' /* [ • • E ] */
#define IC_LANG_RBRAILS		L'' /* [ • F E ] */
#define IC_LANG_RUBY		L'' /* [ • F E ] */
#define IC_LANG_RUST		L'' /* [ • F E ] */
#define IC_LANG_SASS		L'' /* [ • • E ] */
#define IC_LANG_SCHEME		L'' /* [ • • E ] */
#define IC_LANG_STYLUS		L'' /* [ • • E ] */
#define IC_LANG_TEX			L'' /* [ • • E ] */
#define IC_LANG_TSCPT		L'' /* [ • F E ] */
#define IC_LANG_V			L'' /* [ • • E ] */
#define IC_LESS				L'' /* [ • • E ] */
#define IC_LIBRARY			L'' /* [ • • E ] — JV */
#define IC_LICENSE			L'' /* [ • F E ] */
#define IC_LISP				L'󰅲' /* [ • • E ] */
#define IC_LOCK				L'' /* [ • F E ] */
#define IC_LOG				L'' /* [ • F E ] */
#define IC_LXDE				L'' /* [ • F • ] */
#define IC_LXQT				L'' /* [ • F • ] */
#define IC_MAGNET			L'' /* [ • • E ] */
#define IC_MAIL				L'󰇰' /* [ D • • ] */
#define IC_MAKE				L'' /* [ • F E ] */
#define IC_MARKDOWN			L'' /* [ • • E ] */
#define IC_MID				L'󰣲' /* [ • • E ] */
#define IC_MOVIES			L'󰿎' /* [ D • • ] */
#define IC_MPV				L'' /* [ • F • ] */
#define IC_MSF				L'' /* [ • • E ] */
#define IC_MUSIC			L'󱍙' /* [ D • • ] */
#define IC_MUSTACHE			L'' /* [ • • E ] */
#define IC_NANO				L'' /* [ • F • ] */
#define IC_NEWS				L'' /* [ • F • ] */
#define IC_NINJA			L'󰝴' /* [ • • E ] */
#define IC_NODEJS			L'' /* [ • F E ] */
#define IC_NORG				L'' /* [ • • E ] */
#define IC_NOTEBOOK			L'' /* [ • • E ] */
#define IC_NPM				L'' /* [ • F • ] */
#define IC_NUXT				L'󱄆' /* [ • F • ] */
#define IC_ODF				L'' /* [ • • E ] */
#define IC_ODG				L'' /* [ • • E ] */
#define IC_ODP				L'' /* [ • • E ] */
#define IC_ODS				L'' /* [ • • E ] */
#define IC_ODT				L'' /* [ • • E ] */
#define IC_OPAM				L'󰘧' /* [ • • E ] */
#define IC_ORG				L'' /* [ • • E ] */
#define IC_OS_ANDROID		L'' /* [ • • E ] */
#define IC_OS_APPLE			L'' /* [ • F E ] */
#define IC_OS_LINUX			L'' /* [ • • E ] */
#define IC_OS_WINDOWS		L'' /* [ • • E ] */
#define IC_OS_WINDOWS_CMD	L'' /* [ • • E ] */
#define IC_OUT				L'' /* [ • • E ] */
#define IC_PAINTBRUSH		L'' /* [ • F • ] */
#define IC_PDF				L'' /* [ • • E ] */
#define IC_PEOPLE			L'' /* [ • F • ] */
#define IC_PHOTOSHOP		L'' /* [ • • E ] */
#define IC_PICTURES			L'󰉏' /* [ D • • ] */
#define IC_PKG				L'' /* [ • • E ] */
#define IC_PLATFORMIO		L'' /* [ • F • ] */
#define IC_PLAYLIST			L'󰲹' /* [ • • E ] */
#define IC_POM				L'' /* [ • F • ] */
#define IC_POWERSHELL		L'' /* [ • • E ] */
#define IC_PP				L'' /* [ • • E ] */
#define IC_PRETTIER			L'' /* [ • F • ] */
#define IC_PRIVATE_KEY		L'󰌆' /* [ • F • ] */
#define IC_PRUSASLICER		L'' /* [ • F • ] */
#define IC_PUBLIC_KEY		L'󰷖' /* [ • • E ] */
#define IC_PURS				L'' /* [ • • E ] */
#define IC_QT				L'' /* [ • F E ] */
#define IC_RAZOR			L'' /* [ • • E ] */
#define IC_RDB				L'' /* [ • • E ] */
#define IC_REACT			L'' /* [ • • E ] */
#define IC_README			L'󰂺' /* [ • F E ] */
#define IC_RENOVATE			L'󰉼' /* [ • F • ] */
#define IC_ROBOT			L'󰚩' /* [ • F • ] */
#define IC_RPM				L'' /* [ • • E ] */
#define IC_RSS				L'' /* [ • • E ] */
#define IC_SCAD				L'' /* [ • • E ] */
#define IC_SCALA			L'' /* [ • • E ] */
#define IC_SECURITY			L'󰒃' /* [ • F • ] */
#define IC_SERVICE			L'' /* [ • • E ] */
#define IC_SHEET			L'' /* [ • • E ] */
#define IC_SHELL			L'󱆃' /* [ • F E ] */
#define IC_SHELL_CMD		L'' /* [ • F E ] */
#define IC_SHIELD_CHECK		L'󰕥' /* [ • • E ] */
#define IC_SHIELD_KEY		L'󰯄' /* [ • • E ] */
#define IC_SHIELD_LOCK		L'󰦝' /* [ • • E ] */
#define IC_SIGNED_FILE		L'󱧃' /* [ • • E ] */
#define IC_SLIDE			L'' /* [ • • E ] */
#define IC_SQ_WAVE			L'󱑻' /* [ • • E ] */
#define IC_SQLITE			L'' /* [ • • E ] */
#define IC_SRC				L'󰣞' /* [ D • • ] */
#define IC_SSH_LOGO			L'󰣀' /* [ • F • ] */
#define IC_STAR				L'' /* [ • F • ] */
#define IC_STOW				L'' /* [ • F • ] */
#define IC_SUBLIME			L'' /* [ • • E ] */
#define IC_SUBTITLE			L'󰨖' /* [ • • E ] */
#define IC_SVELTE			L'' /* [ • • E ] */
#define IC_SWIFT			L'' /* [ • • E ] — JV */
#define IC_SWITCH			L'󰟡' /* [ • • E ] */
#define IC_TCL				L'󰛓' /* [ • • E ] */
#define IC_TERRAFORM		L'󱁢' /* [ • • E ] */
#define IC_TEXT				L'' /* [ • • E ] */
#define IC_TMUX				L'' /* [ • F E ] */
#define IC_TODO				L'' /* [ • F • ] */
#define IC_TOML				L'' /* [ • • E ] */
#define IC_TORRENT			L'' /* [ • • E ] */
#define IC_TRANSLATION		L'󰗊' /* [ • • E ] */
#define IC_TRASH			L'' /* [ D • • ] */
#define IC_TREB_CLEF		L'󰽰' /* [ • • E ] */
#define IC_TWIG				L'' /* [ • • E ] */
#define IC_TYPST			L'' /* [ • • E ] */
#define IC_UI				L'' /* [ • • E ] */
#define IC_UNITY			L'' /* [ • • E ] */
#define IC_VAGRANT			L'⍱' /* [ • F • ] */
#define IC_VALA				L'' /* [ • • E ] */
#define IC_VECTOR			L'󰕙' /* [ • • E ] */
#define IC_VHS				L'󰨛' /* [ • • E ] */
#define IC_VI				L'' /* [ • • E ] */
#define IC_VIDEOS			L'' /* [ D • E ] */
#define IC_VIM				L'' /* [ • F E ] */
#define IC_VLC				L'󰕼' /* [ • F • ] */
#define IC_VSCODE			L'' /* [ • • E ] */
#define IC_VSIX				L'󰨞' /* [ • • E ] */
#define IC_VUE				L'󰡄' /* [ • • E ] */
#define IC_WEBPACK			L'󰜫' /* [ • F • ] */
#define IC_WESTON			L'' /* [ • F • ] */
#define IC_WRENCH			L'' /* [ • F • ] */
#define IC_XAML				L'󰙳' /* [ • • E ] */
#define IC_XML				L'󰗀' /* [ • • E ] */
#define IC_XORG				L'' /* [ • F • ] */
#define IC_XPI				L'' /* [ • • E ] */
#define IC_YAML				L'' /* [ • • • ] */
#define IC_YARN				L'' /* [ • F • ] */
#define IC_ZIG				L'' /* [ • F E ] */


#define IC_JV				L'↧'
#define IC_APP				L''
#define IC_ARCHIVE			L'󱝏'
#define IC_BACKUP_DIR		L'󰴋'
#define IC_BACKUP_FILE		L'󰁯'
#define IC_RESOURCES		L'󱂸'
#define IC_APPLICATIONS		L''
#define IC_NOFOLLOW         L''
#define IC_RESOLVE          L'󰕟'
#define IC_VOLUME           L'󰥠'
#define IC_COREDUMP         L''
#define IC_DEVICES          L'󰾰'
#define IC_OPT              L''
#define IC_SYSTEM           L'󰡀'
#define IC_TEMP             L'󰔛'
#define IC_USERS            L''
#define IC_USER             L''
#define IC_VAR              L'󰫧'
#define IC_SHARED           L'󱒃'
#define IC_DEBUG            L''
#define IC_LAPTOP           L''
#define IC_VSC_SHARED       L''
#define IC_PUBLIC           L'󰛍'

#define IC_CHIP				L''
#define IC_BUILDING			L'󱔟'
#define IC_CROWN			L''
#define IC_ROSE				L'󰧲'
#define IC_CAR				L'󰞬'
#define IC_HAMMER			L'󰣪'
#define IC_SHIP				L''
#define IC_CAMERA			L'󰄀'
#define IC_GRAD_CAP			L''

#define IC_DISCORD          L''
#define IC_KEYBOARD         L''
#define IC_MAN_PAGES        L'󰺄'
#define IC_RAYCAST          L''
#define IC_LANG_SHELL       L''
#define IC_WEB              L'󰖟'
#define IC_GEAR             L''

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— Default Icons ———————————————————————————————————————————————————————————————————————————————————————————————— */

const icon_t DEFAULT_FILE_ICON = IC_FILE;
const icon_t UNKNOWN_EXT_ICON  = IC_FILE_UNKNOWN;
const icon_t DEFAULT_DIR_ICON  = IC_FOLDER;

/* —— Directory Icons —————————————————————————————————————————————————————————————————————————————————————————————— */

/// An array containing the basenames of directories, and their associated icons.
/// This array should contain all the directories that have custom icons.
const Icon DIRNAME_ICONS[] = {
	{ ".config"			, IC_FOLDER_CONFIG	}, // 
	{ ".exercism"		, IC_EXERCISM		}, // 
	{ ".git"			, IC_FOLDER_GIT		}, // 󰊢  – JV
	{ ".github"			, IC_FOLDER_GITHUB	}, // 
	{ ".npm"			, IC_FOLDER_NPM		}, // 
	{ ".opam"			, IC_LANG_OCAML		}, // 
	{ ".ssh"			, IC_FOLDER_KEY		}, // 󰢬
	{ ".trash"			, IC_TRASH			}, // 
	{ "build"			, IC_FOLDER_BUILD	}, // 󱧼
	{ "cabal"			, IC_LANG_HASKELL	}, // 
	{ "config"			, IC_FOLDER_CONFIG	}, // 
	{ "contacts"		, IC_CONTACTS		}, // 󰉌
	{ "cron.d"			, IC_FOLDER_CONFIG	}, // 
	{ "cron.daily"		, IC_FOLDER_CONFIG	}, // 
	{ "cron.hourly"		, IC_FOLDER_CONFIG	}, // 
	{ "cron.minutely"	, IC_FOLDER_CONFIG	}, // 
	{ "cron.monthly"	, IC_FOLDER_CONFIG	}, // 
	{ "cron.weekly"		, IC_FOLDER_CONFIG	}, // 
	{ "desktop"			, IC_DESKTOP		}, // 
	{ "documents"		, IC_DOCUMENTS		}, // 󰲂
	{ "downloads"		, IC_DOWNLOADS		}, // 󰉍
	{ "etc"				, IC_FOLDER_CONFIG	}, // 
	{ "favorites"		, IC_FAVORITES		}, // 󰚝
	{ "hidden"			, IC_FOLDER_HIDDEN	}, // 󱞞
	{ "home"			, IC_HOME			}, // 󱂵
	{ "include"			, IC_FOLDER_CONFIG	}, // 
	{ "mail"			, IC_MAIL			}, // 󰇰
	{ "movies"			, IC_MOVIES			}, // 󰿎
	{ "music"			, IC_MUSIC			}, // 󱍙
	{ "node_modules"	, IC_FOLDER_NPM		}, // 
	{ "npm_cache"		, IC_FOLDER_NPM		}, // 
	{ "pacman.d"		, IC_FOLDER_CONFIG	}, // 
	{ "pam.d"			, IC_FOLDER_KEY		}, // 󰢬
	{ "pictures"		, IC_PICTURES		}, // 󰉏
	{ "src"				, IC_SRC			}, // 󰣞
	{ "source"			, IC_SRC			}, // 󰣞  – JV
	{ "ssh"				, IC_FOLDER_KEY		}, // 󰢬
	{ "sudoers.d"		, IC_FOLDER_KEY		}, // 󰢬
	{ "videos"			, IC_VIDEOS			}, // 
	{ "xbps.d"			, IC_FOLDER_CONFIG	}, // 
	{ "xorg.conf.d"		, IC_FOLDER_CONFIG	}, // 

	{ "jv"				, IC_JV				}, // ↧  – JV
	{ "archive"			, IC_ARCHIVE		},
	{ "archives"		, IC_ARCHIVE		},
	{ ".idea"			, IC_INTELLIJ		}, //   – JV
	{ "bin"				, IC_BINARY			}, //   – JV
	{ "sbin"			, IC_BINARY			}, //   – JV
	{ "private"			, IC_LOCK			}, // 
	{ "resources"		, IC_RESOURCES		}, // 󱂸
	{ "applications"	, IC_APPLICATIONS	},
	{ "apps"			, IC_APPLICATIONS	},
	{ ".nofollow"		, IC_NOFOLLOW		},
	{ ".resolve", IC_RESOLVE },
	{ ".vol", IC_VOLUME },
	{ "volumes", IC_VOLUME },
	{ "cores", IC_COREDUMP },
	{ "dev", IC_DEVICES },
	{ "opt", IC_OPT },
	{ "system", IC_SYSTEM },
	{ "tmp", IC_TEMP },
	{ "users", IC_USERS },
	{ "usr", IC_USER },
	{ "var", IC_VAR },
	{ "shared", IC_SHARED },
	{ "library", IC_LIBRARY },
	{ "lib", IC_LIBRARY },
	{ "debug", IC_DEBUG },
	{ "debugging", IC_DEBUG },
	{ ".cache", IC_CACHE },
	{ ".local", IC_LAPTOP },
	{ ".swiftpm", IC_SWIFT },
	{ ".vscode", IC_VSCODE },
	{ ".vscode-shared", IC_VSC_SHARED },
	{ "public", IC_PUBLIC },

	{ "cs", IC_CHIP },
	{ "ey", IC_BUILDING },
	{ "house of lords", IC_CROWN },
	{ "labour", IC_ROSE },
	{ "mclaren", IC_CAR },
	{ "old desktop", IC_DESKTOP },
	{ "ra", IC_HAMMER },
	{ "rn", IC_SHIP },
	{ "screenshots", IC_CAMERA },
	{ "university work", IC_GRAD_CAP },

	{ "applescript", IC_OS_APPLE },
	{ "c#", IC_LANG_CSHARP },
	{ "discord", IC_DISCORD },
	{ "karabiner", IC_KEYBOARD },
	{ "jave", IC_LANG_JAVA },
	{ "man pages", IC_MAN_PAGES },
	{ "python", IC_LANG_PYTHON },
	{ "raycast", IC_RAYCAST },
	{ "rust", IC_LANG_RUST },
	{ "shellscript", IC_LANG_SHELL },
	{ "swift", IC_SWIFT },
	{ "vs_code", IC_VSCODE },
	{ "web", IC_WEB },
	{ "java", IC_LANG_JAVA },
	{ "c", IC_LANG_C },
	{ "x_automation", IC_ROBOT },
	{ "y_settings_etc", IC_GEAR },
	{ "z_other", IC_ARCHIVE },
	{ "hdd", IC_VOLUME },

	END_OF_ICONS
};

/* —— Filename Icons ——————————————————————————————————————————————————————————————————————————————————————————————— */

/// Array containing full filenames & their icons.
const Icon FILENAME_ICONS[] = {
	{ ".VolumeIcon.icns"			, IC_IMAGE				},
	{ ".localized"					, IC_TRANSLATION		}, // 󰗊  — JV
	{ "hdd", IC_VOLUME },

	{ "._ds_store"					, IC_OS_APPLE			}, // 
	{ ".aliases"					, IC_SHELL				}, // 󱆃
	{ ".atom"						, IC_ATOM				}, // 
	{ ".bash_aliases"				, IC_SHELL				}, // 󱆃
	{ ".bash_history"				, IC_SHELL				}, // 󱆃
	{ ".bash_logout"				, IC_SHELL				}, // 󱆃
	{ ".bash_profile"				, IC_SHELL				}, // 󱆃
	{ ".bashrc"						, IC_SHELL				}, // 󱆃
	{ ".cfusertextencoding"			, IC_TRANSLATION		}, // 󰗊  — JV
	{ ".clang-format"				, IC_CONFIG				}, // 󱁻
	{ ".clang-tidy"					, IC_CONFIG				}, // 󱁻
	{ ".codespellrc"				, IC_CODESPELL			}, // 󰓆
	{ ".condarc"					, IC_CONDA				}, // 
	{ ".cshrc"						, IC_SHELL				}, // 󱆃
	{ ".ds_store"					, IC_OS_APPLE			}, // 
	{ ".editorconfig"				, IC_EDITORCONFIG		}, // 
	{ ".emacs"						, IC_EMACS				}, // 
	{ ".envrc"						, IC_ENV				}, // 
	{ ".eslintignore"				, IC_ESLINT				}, // 
	{ ".eslintrc.cjs"				, IC_ESLINT				}, // 
	{ ".eslintrc.js"				, IC_ESLINT				}, // 
	{ ".eslintrc.json"				, IC_ESLINT				}, // 
	{ ".eslintrc.yaml"				, IC_ESLINT				}, // 
	{ ".eslintrc.yml"				, IC_ESLINT				}, // 
	{ ".fennelrc"					, IC_LANG_FENNEL		}, // 
	{ ".gcloudignore"				, IC_GOOGLE_CLOUD		}, // 󱇶
	{ ".git-blame-ignore-revs"		, IC_GIT				}, // 󰊢
	{ ".gitattributes"				, IC_GIT				}, // 󰊢
	{ ".gitconfig"					, IC_GIT				}, // 󰊢
	{ ".gitignore"					, IC_GIT				}, // 󰊢
	{ ".gitignore_global"			, IC_GIT				}, // 󰊢
	{ ".gitlab-ci.yml"				, IC_GITLAB				}, // 
	{ ".gitmodules"					, IC_GIT				}, // 󰊢
	{ ".gtkrc-2.0"					, IC_GRUNT				}, // 
	{ ".gvimrc"						, IC_VIM				}, // 
	{ ".htaccess"					, IC_CONFIG				}, // 󱁻
	{ ".htpasswd"					, IC_CONFIG				}, // 󱁻
	{ ".idea"						, IC_INTELLIJ			}, // 
	{ ".ideavimrc"					, IC_VIM				}, // 
	{ ".inputrc"					, IC_CONFIG				}, // 󱁻
	{ ".kshrc"						, IC_SHELL				}, // 󱆃
	{ ".login"						, IC_SHELL				}, // 󱆃
	{ ".logout"						, IC_SHELL				}, // 󱆃
	{ ".luacheckrc"					, IC_CONFIG				}, // 󱁻
	{ ".luaurc"						, IC_CONFIG				}, // 󱁻
	{ ".mailmap"					, IC_GIT				}, // 󰊢
	{ ".nanorc"						, IC_NANO				}, // 
	{ ".node_repl_history"			, IC_NODEJS				}, // 
	{ ".npmignore"					, IC_NPM				}, // 
	{ ".npmrc"						, IC_NPM				}, // 
	{ ".nuxtrc"						, IC_NUXT				}, // 󱄆
	{ ".ocamlinit"					, IC_LANG_OCAML			}, // 
	{ ".parentlock"					, IC_LOCK				}, // 
	{ ".pre-commit-config.yaml"		, IC_HOOK				}, // 󰛢
	{ ".prettierignore"				, IC_PRETTIER			}, // 
	{ ".prettierrc"					, IC_PRETTIER			}, // 
	{ ".prettierrc.json"			, IC_PRETTIER			}, // 
	{ ".prettierrc.json5"			, IC_PRETTIER			}, // 
	{ ".prettierrc.toml"			, IC_PRETTIER			}, // 
	{ ".prettierrc.yaml"			, IC_PRETTIER			}, // 
	{ ".prettierrc.yml"				, IC_PRETTIER			}, // 
	{ ".profile"					, IC_SHELL				}, // 󱆃
	{ ".pylintrc"					, IC_CONFIG				}, // 󱁻
	{ ".python_history"				, IC_LANG_PYTHON		}, // 
	{ ".rustfmt.toml"				, IC_LANG_RUST			}, // 
	{ ".rvm"						, IC_LANG_RUBY			}, // 
	{ ".rvmrc"						, IC_LANG_RUBY			}, // 
	{ ".srcinfo"					, IC_ARCHBTW			}, // 
	{ ".stowrc"						, IC_STOW				}, // 
	{ ".tcshrc"						, IC_SHELL				}, // 󱆃
	{ ".viminfo"					, IC_VIM				}, // 
	{ ".vimrc"						, IC_VIM				}, // 
	{ ".xauthority"					, IC_XORG				}, // 
	{ ".xinitrc"					, IC_XORG				}, // 
	{ ".xresources"					, IC_XORG				}, // 
	{ ".xsession"					, IC_XORG				}, // 
	{ ".yarnrc"						, IC_YARN				}, // 
	{ ".zlogin"						, IC_SHELL				}, // 󱆃
	{ ".zlogout"					, IC_SHELL				}, // 󱆃
	{ ".zprofile"					, IC_SHELL				}, // 󱆃
	{ ".zsh_history"				, IC_SHELL				}, // 󱆃
	{ ".zsh_sessions"				, IC_SHELL				}, // 󱆃
	{ ".zshenv"						, IC_SHELL				}, // 󱆃
	{ ".zshrc"						, IC_SHELL				}, // 󱆃
	{ "_gvimrc"						, IC_VIM				}, // 
	{ "_vimrc"						, IC_VIM				}, // 
	{ "a.out"						, IC_SHELL_CMD			}, // 
	{ "authorized_keys"				, IC_SSH_LOGO			}, // 󰣀
	{ "authors"						, IC_PEOPLE				}, // 
	{ "authors.txt"					, IC_PEOPLE				}, // 
	{ "bashrc"						, IC_SHELL				}, // 󱆃
	{ "brewfile"					, IC_HOMEBREW			}, // 󱄖
	{ "brewfile.lock.json"			, IC_HOMEBREW			}, // 󱄖
	{ "bspwmrc"						, IC_BSPWM				}, // 
	{ "build.gradle.kts"			, IC_GRADLE				}, // 
	{ "build.zig.zon"				, IC_ZIG				}, // 
	{ "bun.lockb"					, IC_BUN				}, // 
	{ "cantorrc"					, IC_KDE				}, // 
	{ "cargo.lock"					, IC_LANG_RUST			}, // 
	{ "cargo.toml"					, IC_LANG_RUST			}, // 
	{ "changelog"					, IC_NEWS				}, // 
	{ "changelog.md"				, IC_NEWS				}, // 
	{ "changes"						, IC_NEWS				}, // 
	{ "changes.md"					, IC_NEWS				}, // 
	{ "cmakelists.txt"				, IC_CMAKE				}, // 
	{ "code_of_conduct"				, IC_CODE_OF_CONDUCT	}, // 
	{ "code_of_conduct.md"			, IC_CODE_OF_CONDUCT	}, // 
	{ "commit_editmsg"				, IC_GIT				}, // 󰊢
	{ "compose.yaml"				, IC_DOCKER				}, // 
	{ "compose.yml"					, IC_DOCKER				}, // 
	{ "composer.json"				, IC_LANG_PHP			}, // 
	{ "composer.lock"				, IC_LANG_PHP			}, // 
	{ "config"						, IC_CONFIG				}, // 󱁻
	{ "config.ru"					, IC_LANG_RUBY			}, // 
	{ "config.status"				, IC_CONFIG				}, // 󱁻
	{ "configure"					, IC_WRENCH				}, // 
	{ "configure.ac"				, IC_CONFIG				}, // 󱁻
	{ "configure.in"				, IC_CONFIG				}, // 󱁻
	{ "constraints.txt"				, IC_LANG_PYTHON		}, // 
	{ "copying"						, IC_LICENSE			}, // 
	{ "copyright"					, IC_LICENSE			}, // 
	{ "crontab"						, IC_CONFIG				}, // 󱁻
	{ "crypttab"					, IC_CONFIG				}, // 󱁻
	{ "csh.cshrc"					, IC_SHELL				}, // 󱆃
	{ "csh.login"					, IC_SHELL				}, // 󱆃
	{ "csh.logout"					, IC_SHELL				}, // 󱆃
	{ "docker-compose.yaml"			, IC_DOCKER				}, // 
	{ "docker-compose.yml"			, IC_DOCKER				}, // 
	{ "dockerfile"					, IC_DOCKER				}, // 
	{ "dropbox"						, IC_DROPBOX			}, // 
	{ "dune"						, IC_LANG_OCAML			}, // 
	{ "dune-project"				, IC_WRENCH				}, // 
	{ "earthfile"					, IC_EARTH				}, // 
	{ "environment"					, IC_CONFIG				}, // 󱁻
	{ "favicon.ico"					, IC_STAR				}, // 
	{ "fennelrc"					, IC_LANG_FENNEL		}, // 
	{ "flake.lock"					, IC_FLAKE				}, // 
	{ "fonts.conf"					, IC_FONT				}, // 
	{ "fp-info-cache"				, IC_KICAD				}, // 
	{ "fp-lib-table"				, IC_KICAD				}, // 
	{ "freecad.conf"				, IC_FREECAD			}, // 
	{ "gemfile"						, IC_LANG_RUBY			}, // 
	{ "gemfile.lock"				, IC_LANG_RUBY			}, // 
	{ "gnumakefile"					, IC_MAKE				}, // 
	{ "go.mod"						, IC_LANG_GO			}, // 
	{ "go.sum"						, IC_LANG_GO			}, // 
	{ "go.work"						, IC_LANG_GO			}, // 
	{ "gradle"						, IC_GRADLE				}, // 
	{ "gradle.properties"			, IC_GRADLE				}, // 
	{ "gradlew"						, IC_GRADLE				}, // 
	{ "gradlew.bat"					, IC_GRADLE				}, // 
	{ "group"						, IC_LOCK				}, // 
	{ "gruntfile.coffee"			, IC_GRUNT				}, // 
	{ "gruntfile.js"				, IC_GRUNT				}, // 
	{ "gruntfile.ls"				, IC_GRUNT				}, // 
	{ "gshadow"						, IC_LOCK				}, // 
	{ "gtkrc"						, IC_GRUNT				}, // 
	{ "gulpfile.coffee"				, IC_GULP				}, // 
	{ "gulpfile.js"					, IC_GULP				}, // 
	{ "gulpfile.ls"					, IC_GULP				}, // 
	{ "heroku.yml"					, IC_HEROKU				}, // 
	{ "hostname"					, IC_CONFIG				}, // 󱁻
	{ "hypridle.conf"				, IC_HYPRLAND			}, // 
	{ "hyprland.conf"				, IC_HYPRLAND			}, // 
	{ "hyprlock.conf"				, IC_HYPRLAND			}, // 
	{ "hyprpaper.conf"				, IC_HYPRLAND			}, // 
	{ "i3blocks.conf"				, IC_I3					}, // 
	{ "i3status.conf"				, IC_I3					}, // 
	{ "id_dsa"						, IC_PRIVATE_KEY		}, // 󰌆
	{ "id_ecdsa"					, IC_PRIVATE_KEY		}, // 󰌆
	{ "id_ecdsa_sk"					, IC_PRIVATE_KEY		}, // 󰌆
	{ "id_ed25519"					, IC_PRIVATE_KEY		}, // 󰌆
	{ "id_ed25519_sk"				, IC_PRIVATE_KEY		}, // 󰌆
	{ "id_rsa"						, IC_PRIVATE_KEY		}, // 󰌆
	{ "index.theme"					, IC_PAINTBRUSH			}, // 
	{ "inputrc"						, IC_CONFIG				}, // 󱁻
	{ "jenkinsfile"					, IC_JENKINSFILE		}, // 
	{ "jsconfig.json"				, IC_LANG_JSCPT			}, // 
	{ "justfile"					, IC_WRENCH				}, // 
	{ "justfile"					, IC_WRENCH				}, // 
	{ "kalgebrarc"					, IC_KDE				}, // 
	{ "kdeglobals"					, IC_KDE				}, // 
	{ "kdenlive-layoutsrc"			, IC_KDENLIVE			}, // 
	{ "kdenliverc"					, IC_KDENLIVE			}, // 
	{ "known_hosts"					, IC_SSH_LOGO			}, // 󰣀
	{ "kritadisplayrc"				, IC_KRITA				}, // 
	{ "kritarc"						, IC_KRITA				}, // 
	{ "licence"						, IC_LICENSE			}, // 
	{ "licence.md"					, IC_LICENSE			}, // 
	{ "licence.txt"					, IC_LICENSE			}, // 
	{ "license"						, IC_LICENSE			}, // 
	{ "license-apache"				, IC_LICENSE			}, // 
	{ "license-mit"					, IC_LICENSE			}, // 
	{ "license.md"					, IC_LICENSE			}, // 
	{ "license.txt"					, IC_LICENSE			}, // 
	{ "localized"					, IC_OS_APPLE			}, // 
	{ "localtime"					, IC_CLOCK				}, // 
	{ "lock"						, IC_LOCK				}, // 
	{ "lock"						, IC_LOCK				}, // 
	{ "log"							, IC_LOG				}, // 
	{ "log"							, IC_LOG				}, // 
	{ "lxde-rc.xml"					, IC_LXDE				}, // 
	{ "lxqt.conf"					, IC_LXQT				}, // 
	{ "makefile"					, IC_MAKE				}, // 
	{ "makefile"					, IC_MAKE				}, // 
	{ "makefile.ac"					, IC_MAKE				}, // 
	{ "makefile.am"					, IC_MAKE				}, // 
	{ "makefile.in"					, IC_MAKE				}, // 
	{ "manifest"					, IC_LANG_PYTHON		}, // 
	{ "manifest.in"					, IC_LANG_PYTHON		}, // 
	{ "mix.lock"					, IC_LANG_ELIXIR		}, // 
	{ "mpv.conf"					, IC_MPV				}, // 
	{ "news"						, IC_NEWS				}, // 
	{ "news.md"						, IC_NEWS				}, // 
	{ "npm-shrinkwrap.json"			, IC_NPM				}, // 
	{ "npmrc"						, IC_NPM				}, // 
	{ "package-lock.json"			, IC_NPM				}, // 
	{ "package.json"				, IC_NPM				}, // 
	{ "passwd"						, IC_LOCK				}, // 
	{ "php.ini"						, IC_LANG_PHP			}, // 
	{ "pkgbuild"					, IC_ARCHBTW			}, // 
	{ "platformio.ini"				, IC_PLATFORMIO			}, // 
	{ "pom.xml"						, IC_POM				}, // 
	{ "procfile"					, IC_HEROKU				}, // 
	{ "profile"						, IC_SHELL				}, // 󱆃
	{ "prusaslicer.ini"				, IC_PRUSASLICER		}, // 
	{ "prusaslicergcodeviewer.ini"	, IC_PRUSASLICER		}, // 
	{ "pyproject.toml"				, IC_LANG_PYTHON		}, // 
	{ "pyvenv.cfg"					, IC_LANG_PYTHON		}, // 
	{ "qt5ct.conf"					, IC_QT					}, // 
	{ "qt6ct.conf"					, IC_QT					}, // 
	{ "qtproject.conf"				, IC_QT					}, // 
	{ "rakefile"					, IC_LANG_RUBY			}, // 
	{ "readme"						, IC_README				}, // 󰂺
	{ "readme.md"					, IC_README				}, // 󰂺
	{ "release.toml"				, IC_LANG_RUST			}, // 
	{ "renovate.json"				, IC_RENOVATE			}, // 󰉼
	{ "requirements.txt"			, IC_LANG_PYTHON		}, // 
	{ "robots.txt"					, IC_ROBOT				}, // 󰚩
	{ "rubydoc"						, IC_LANG_RBRAILS		}, // 
	{ "rvmrc"						, IC_LANG_RUBY			}, // 
	{ "security"					, IC_SECURITY			}, // 󰒃
	{ "security.md"					, IC_SECURITY			}, // 󰒃
	{ "settings.gradle.kts"			, IC_GRADLE				}, // 
	{ "shadow"						, IC_LOCK				}, // 
	{ "shells"						, IC_CONFIG				}, // 󱁻
	{ "sudoers"						, IC_LOCK				}, // 
	{ "sxhkdrc"						, IC_CONFIG				}, // 󱁻
	{ "sym-lib-table"				, IC_KICAD				}, // 
	{ "timezone"					, IC_CLOCK				}, // 
	{ "tmux.conf"					, IC_TMUX				}, // 
	{ "tmux.conf.local"				, IC_TMUX				}, // 
	{ "todo"						, IC_TODO				}, // 
	{ "todo.md"						, IC_TODO				}, // 
	{ "tsconfig.json"				, IC_LANG_TSCPT			}, // 
	{ "vagrantfile"					, IC_VAGRANT			}, // ⍱
	{ "vlcrc"						, IC_VLC				}, // 󰕼
	{ "webpack.config.js"			, IC_WEBPACK			}, // 󰜫
	{ "weston.ini"					, IC_WESTON				}, // 
	{ "xmobarrc"					, IC_XORG				}, // 
	{ "xmobarrc.hs"					, IC_XORG				}, // 
	{ "xmonad.hs"					, IC_XORG				}, // 
	{ "xorg.conf"					, IC_XORG				}, // 
	{ "xsettingsd.conf"				, IC_XORG				}, // 
	{ "yarn.lock"					, IC_YARN				}, // 
	{ "zlogin"						, IC_SHELL				}, // 󱆃
	{ "zlogout"						, IC_SHELL				}, // 󱆃
	{ "zprofile"					, IC_SHELL				}, // 󱆃
	{ "zshenv"						, IC_SHELL				}, // 󱆃
	{ "zshrc"						, IC_SHELL				}, // 󱆃
	END_OF_ICONS
};

/* —— Directory Extension Icons ———————————————————————————————————————————————————————————————————————————————————— */

/// Array of lowercase file extensions and their icons.
const Icon DIR_EXT_ICONS[] = {
	{ "bak"				, IC_BACKUP_DIR		}, // 󰴋  – JV
	{ "app"				, IC_APP			}, //   – JV
	END_OF_ICONS
};

/* —— File Extension Icons ————————————————————————————————————————————————————————————————————————————————————————— */

/// Array of lowercase file extensions and their icons.
const Icon FILE_EXT_ICONS[] = {
	{ "ai"				, IC_AI				}, // 
	{ "cr"				, IC_CR				}, // 
	{ "cu"				, IC_CU				}, // 
	{ "jl"				, IC_JL				}, // 
	{ "pp"				, IC_PP				}, // 
	{ "qss"				, IC_QT				}, // 
	{ "qrc"				, IC_QT				}, // 
	{ "qml"				, IC_QT				}, // 
	{ "ui"				, IC_UI				}, // 
	{ "vi"				, IC_VI				}, // 
	{ "acf"				, IC_ACF			}, // 
	{ "asp"				, IC_ASP			}, // 
	{ "x_t"				, IC_CAD			}, // 󰻫
	{ "x_b"				, IC_CAD			}, // 󰻫
	{ "stp"				, IC_CAD			}, // 󰻫
	{ "step"			, IC_CAD			}, // 󰻫
	{ "ste"				, IC_CAD			}, // 󰻫
	{ "slvs"			, IC_CAD			}, // 󰻫
	{ "sldprt"			, IC_CAD			}, // 󰻫
	{ "sldasm"			, IC_CAD			}, // 󰻫
	{ "skp"				, IC_CAD			}, // 󰻫
	{ "psm"				, IC_CAD			}, // 󰻫
	{ "ipt"				, IC_CAD			}, // 󰻫
	{ "igs"				, IC_CAD			}, // 󰻫
	{ "iges"			, IC_CAD			}, // 󰻫
	{ "ige"				, IC_CAD			}, // 󰻫
	{ "ifc"				, IC_CAD			}, // 󰻫
	{ "iam"				, IC_CAD			}, // 󰻫
	{ "f3z"				, IC_CAD			}, // 󰻫
	{ "f3d"				, IC_CAD			}, // 󰻫
	{ "dxf"				, IC_CAD			}, // 󰻫
	{ "dwg"				, IC_CAD			}, // 󰻫
	{ "catproduct"		, IC_CAD			}, // 󰻫
	{ "catpart"			, IC_CAD			}, // 󰻫
	{ "brep"			, IC_CAD			}, // 󰻫
	{ "3dm"				, IC_CAD			}, // 󰻫
	{ "123dx"			, IC_CAD			}, // 󰻫
	{ "com"				, IC_COM			}, // 
	{ "cow"				, IC_COW			}, // 󰆚
	{ "csv"				, IC_CSV			}, // 
	{ "deb"				, IC_DEB			}, // 
	{ "ejs"				, IC_EJS			}, // 
	{ "elm"				, IC_ELM			}, // 
	{ "eml"				, IC_EML			}, // 
	{ "env"				, IC_ENV			}, // 
	{ "z64"				, IC_GBA			}, // 󱎓
	{ "gba"				, IC_GBA			}, // 󱎓
	{ "git"				, IC_GIT			}, // 󰊢
	{ "gresource"		, IC_GTK			}, // 
	{ "hex"				, IC_HEX			}, // 󱊧
	{ "pfx"				, IC_KEY			}, // 
	{ "pem"				, IC_KEY			}, // 
	{ "p12"				, IC_KEY			}, // 
	{ "key"				, IC_KEY			}, // 
	{ "log"				, IC_LOG			}, // 
	{ "mid"				, IC_MID			}, // 󰣲
	{ "msf"				, IC_MSF			}, // 
	{ "odf"				, IC_ODF			}, // 
	{ "odg"				, IC_ODG			}, // 
	{ "fodg"			, IC_ODG			}, // 
	{ "odp"				, IC_ODP			}, // 
	{ "fodp"			, IC_ODP			}, // 
	{ "ods"				, IC_ODS			}, // 
	{ "fods"			, IC_ODS			}, // 
	{ "odt"				, IC_ODT			}, // 
	{ "fodt"			, IC_ODT			}, // 
	{ "org"				, IC_ORG			}, // 
	{ "out"				, IC_OUT			}, // 
	{ "pdf"				, IC_PDF			}, // 
	{ "pkg"				, IC_PKG			}, // 
	{ "rdb"				, IC_RDB			}, // 
	{ "rpm"				, IC_RPM			}, // 
	{ "rss"				, IC_RSS			}, // 
	{ "tcl"				, IC_TCL			}, // 󰛓
	{ "tbc"				, IC_TCL			}, // 󰛓
	{ "vhs"				, IC_VHS			}, // 󰨛
	{ "vim"				, IC_VIM			}, // 
	{ "vue"				, IC_VUE			}, // 󰡄
	{ "xul"				, IC_XML			}, // 󰗀
	{ "xml"				, IC_XML			}, // 󰗀
	{ "opml"			, IC_XML			}, // 󰗀
	{ "xpi"				, IC_XPI			}, // 
	{ "zig"				, IC_ZIG			}, // 
	{ "mobi"			, IC_BOOK			}, // 
	{ "epub"			, IC_BOOK			}, // 
	{ "ebook"			, IC_BOOK			}, // 
	{ "css"				, IC_CSS3			}, // 
	{ "dart"			, IC_DART			}, // 
	{ "patch"			, IC_DIFF			}, // 
	{ "diff"			, IC_DIFF			}, // 
	{ "woff2"			, IC_FONT			}, // 
	{ "woff"			, IC_FONT			}, // 
	{ "ttf"				, IC_FONT			}, // 
	{ "ttc"				, IC_FONT			}, // 
	{ "psf"				, IC_FONT			}, // 
	{ "otf"				, IC_FONT			}, // 
	{ "lff"				, IC_FONT			}, // 
	{ "font"			, IC_FONT			}, // 
	{ "fon"				, IC_FONT			}, // 
	{ "fnt"				, IC_FONT			}, // 
	{ "flf"				, IC_FONT			}, // 
	{ "flc"				, IC_FONT			}, // 
	{ "eot"				, IC_FONT			}, // 
	{ "bdf"				, IC_FONT			}, // 
	{ "xcf"				, IC_GIMP			}, // 
	{ "haml"			, IC_HAML			}, // 
	{ "nfo"				, IC_INFO			}, // 
	{ "info"			, IC_INFO			}, // 
	{ "webmanifest"		, IC_JSON			}, // 
	{ "properties"		, IC_JSON			}, // 
	{ "jsonc"			, IC_JSON			}, // 
	{ "json5"			, IC_JSON			}, // 
	{ "json"			, IC_JSON			}, // 
	{ "avro"			, IC_JSON			}, // 
	{ "less"			, IC_LESS			}, // 
	{ "lisp"			, IC_LISP			}, // 󰅲
	{ "lock"			, IC_LOCK			}, // 
	{ "lck"				, IC_LOCK			}, // 
	{ "mk"				, IC_MAKE			}, // 
	{ "norg"			, IC_NORG			}, // 
	{ "opam"			, IC_OPAM			}, // 󰘧
	{ "purs"			, IC_PURS			}, // 
	{ "scad"			, IC_SCAD			}, // 
	{ "txt"				, IC_TEXT			}, // 
	{ "rtf"				, IC_TEXT			}, // 
	{ "rst"				, IC_TEXT			}, // 
	{ "tmux"			, IC_TMUX			}, // 
	{ "toml"			, IC_TOML			}, // 
	{ "twig"			, IC_TWIG			}, // 
	{ "vala"			, IC_VALA			}, // 
	{ "vsix"			, IC_VSIX			}, // 󰨞
	{ "xaml"			, IC_XAML			}, // 󰙳
	{ "yml"				, IC_YAML			}, // 
	{ "yaml"			, IC_YAML			}, // 
	{ "wv"				, IC_AUDIO			}, // 
	{ "wma"				, IC_AUDIO			}, // 
	{ "wav"				, IC_AUDIO			}, // 
	{ "swf"				, IC_AUDIO			}, // 
	{ "pcm"				, IC_AUDIO			}, // 
	{ "opus"			, IC_AUDIO			}, // 
	{ "ogg"				, IC_AUDIO			}, // 
	{ "mp3"				, IC_AUDIO			}, // 
	{ "mp2"				, IC_AUDIO			}, // 
	{ "mka"				, IC_AUDIO			}, // 
	{ "m4a"				, IC_AUDIO			}, // 
	{ "flac"			, IC_AUDIO			}, // 
	{ "ape"				, IC_AUDIO			}, // 
	{ "alac"			, IC_AUDIO			}, // 
	{ "aiff"			, IC_AUDIO			}, // 
	{ "aifc"			, IC_AUDIO			}, // 
	{ "aif"				, IC_AUDIO			}, // 
	{ "aac"				, IC_AUDIO			}, // 
	{ "blend"			, IC_BLEND			}, // 󰂫
	{ "cache"			, IC_CACHE			}, // 
	{ "cmake"			, IC_CMAKE			}, // 
	{ "conda"			, IC_CONDA			}, // 
	{ "elc"				, IC_EMACS			}, // 
	{ "el"				, IC_EMACS			}, // 
	{ "nix"				, IC_FLAKE			}, // 
	{ "gcode"			, IC_GCODE			}, // 󰫴
	{ "gform"			, IC_GFORM			}, // 
	{ "tscn"			, IC_GODOT			}, // 
	{ "tres"			, IC_GODOT			}, // 
	{ "godot"			, IC_GODOT			}, // 
	{ "gd"				, IC_GODOT			}, // 
	{ "gv"				, IC_GRAPH			}, // 󱁉
	{ "dot"				, IC_GRAPH			}, // 󱁉
	{ "xhtml"			, IC_HTML5			}, // 
	{ "shtml"			, IC_HTML5			}, // 
	{ "html"			, IC_HTML5			}, // 
	{ "htm"				, IC_HTML5			}, // 
	{ "xpm"				, IC_IMAGE			}, // 
	{ "webp"			, IC_IMAGE			}, // 
	{ "tiff"			, IC_IMAGE			}, // 
	{ "tif"				, IC_IMAGE			}, // 
	{ "raw"				, IC_IMAGE			}, // 
	{ "pxm"				, IC_IMAGE			}, // 
	{ "ppm"				, IC_IMAGE			}, // 
	{ "pnm"				, IC_IMAGE			}, // 
	{ "png"				, IC_IMAGE			}, // 
	{ "pgm"				, IC_IMAGE			}, // 
	{ "pbm"				, IC_IMAGE			}, // 
	{ "orf"				, IC_IMAGE			}, // 
	{ "nef"				, IC_IMAGE			}, // 
	{ "jxl"				, IC_IMAGE			}, // 
	{ "jpx"				, IC_IMAGE			}, // 
	{ "jpg"				, IC_IMAGE			}, // 
	{ "jpf"				, IC_IMAGE			}, // 
	{ "jpeg"			, IC_IMAGE			}, // 
	{ "jpe"				, IC_IMAGE			}, // 
	{ "jp2"				, IC_IMAGE			}, // 
	{ "jif"				, IC_IMAGE			}, // 
	{ "jfif"			, IC_IMAGE			}, // 
	{ "jfi"				, IC_IMAGE			}, // 
	{ "j2k"				, IC_IMAGE			}, // 
	{ "j2c"				, IC_IMAGE			}, // 
	{ "ico"				, IC_IMAGE			}, // 
	{ "heif"			, IC_IMAGE			}, // 
	{ "heic"			, IC_IMAGE			}, // 
	{ "gif"				, IC_IMAGE			}, // 
	{ "dvi"				, IC_IMAGE			}, // 
	{ "cr2"				, IC_IMAGE			}, // 
	{ "cbz"				, IC_IMAGE			}, // 
	{ "cbr"				, IC_IMAGE			}, // 
	{ "bmp"				, IC_IMAGE			}, // 
	{ "avif"			, IC_IMAGE			}, // 
	{ "arw"				, IC_IMAGE			}, // 
	{ "jwmrc"			, IC_JWMRC			}, // 
	{ "kicad_wks"		, IC_KICAD			}, // 
	{ "kicad_sym"		, IC_KICAD			}, // 
	{ "kicad_sch"		, IC_KICAD			}, // 
	{ "kicad_pro"		, IC_KICAD			}, // 
	{ "kicad_prl"		, IC_KICAD			}, // 
	{ "kicad_pcb"		, IC_KICAD			}, // 
	{ "kicad_mod"		, IC_KICAD			}, // 
	{ "kicad_dru"		, IC_KICAD			}, // 
	{ "krz"				, IC_KRITA			}, // 
	{ "kra"				, IC_KRITA			}, // 
	{ "kpp"				, IC_KRITA			}, // 
	{ "ninja"			, IC_NINJA			}, // 󰝴
	{ "razor"			, IC_RAZOR			}, // 
	{ "cshtml"			, IC_RAZOR			}, // 
	{ "tsx"				, IC_REACT			}, // 
	{ "jsx"				, IC_REACT			}, // 
	{ "scala"			, IC_SCALA			}, // 
	{ "xlsx"			, IC_SHEET			}, // 
	{ "xlsm"			, IC_SHEET			}, // 
	{ "xls"				, IC_SHEET			}, // 
	{ "xlr"				, IC_SHEET			}, // 
	{ "tsv"				, IC_SHEET			}, // 
	{ "gsheet"			, IC_SHEET			}, // 
	{ "zsh-theme"		, IC_SHELL			}, // 󱆃
	{ "pptx"			, IC_SLIDE			}, // 
	{ "ppt"				, IC_SLIDE			}, // 
	{ "ppsx"			, IC_SLIDE			}, // 
	{ "pps"				, IC_SLIDE			}, // 
	{ "gslides"			, IC_SLIDE			}, // 
	{ "xcplayground"	, IC_SWIFT			}, // 
	{ "swift"			, IC_SWIFT			}, // 
	{ "typ"				, IC_TYPST			}, // 
	{ "unity3d"			, IC_UNITY			}, // 
	{ "unity"			, IC_UNITY			}, // 
	{ "o"				, IC_BINARY			}, // 
	{ "hi"				, IC_BINARY			}, // 
	{ "elf"				, IC_BINARY			}, // 
	{ "bin"				, IC_BINARY			}, // 
	{ "app"				, IC_BINARY			}, // 
	{ "coffee"			, IC_COFFEE			}, // 
	{ "tml"				, IC_CONFIG			}, // 󱁻
	{ "ini"				, IC_CONFIG			}, // 󱁻
	{ "config"			, IC_CONFIG			}, // 󱁻
	{ "conf"			, IC_CONFIG			}, // 󱁻
	{ "cfg"				, IC_CONFIG			}, // 󱁻
	{ "dockerignore"	, IC_DOCKER			}, // 
	{ "dockerfile"		, IC_DOCKER			}, // 
	{ "drawio"			, IC_DRAWIO			}, // 
	{ "ebuild"			, IC_EBUILD			}, // 
	{ "hrl"				, IC_ERLANG			}, // 
	{ "erl"				, IC_ERLANG			}, // 
	{ "gradle"			, IC_GRADLE			}, // 
	{ "m"				, IC_LANG_C			}, // 
	{ "inl"				, IC_LANG_C			}, // 
	{ "h"				, IC_LANG_C			}, // 
	{ "c"				, IC_LANG_C			}, // 
	{ "di"				, IC_LANG_D			}, // 
	{ "d"				, IC_LANG_D			}, // 
	{ "rds"				, IC_LANG_R			}, // 
	{ "rdata"			, IC_LANG_R			}, // 
	{ "r"				, IC_LANG_R			}, // 
	{ "v"				, IC_LANG_V			}, // 
	{ "magnet"			, IC_MAGNET			}, // 
	{ "node"			, IC_NODEJS			}, // 
	{ "readme"			, IC_README			}, // 󰂺
	{ "sqlite3"			, IC_SQLITE			}, // 
	{ "sqlite"			, IC_SQLITE			}, // 
	{ "sl3"				, IC_SQLITE			}, // 
	{ "s3db"			, IC_SQLITE			}, // 
	{ "db3"				, IC_SQLITE			}, // 
	{ "svelte"			, IC_SVELTE			}, // 
	{ "xci"				, IC_SWITCH			}, // 󰟡
	{ "nsp"				, IC_SWITCH			}, // 󰟡
	{ "svg"				, IC_VECTOR			}, // 󰕙
	{ "ps"				, IC_VECTOR			}, // 󰕙
	{ "eps"				, IC_VECTOR			}, // 󰕙
	{ "wmv"				, IC_VIDEOS			}, // 
	{ "webm"			, IC_VIDEOS			}, // 
	{ "vob"				, IC_VIDEOS			}, // 
	{ "video"			, IC_VIDEOS			}, // 
	{ "ogv"				, IC_VIDEOS			}, // 
	{ "ogm"				, IC_VIDEOS			}, // 
	{ "mpg"				, IC_VIDEOS			}, // 
	{ "mpeg"			, IC_VIDEOS			}, // 
	{ "mp4"				, IC_VIDEOS			}, // 
	{ "mov"				, IC_VIDEOS			}, // 
	{ "mkv"				, IC_VIDEOS			}, // 
	{ "m4v"				, IC_VIDEOS			}, // 
	{ "m2v"				, IC_VIDEOS			}, // 
	{ "m2ts"			, IC_VIDEOS			}, // 
	{ "heics"			, IC_VIDEOS			}, // 
	{ "h264"			, IC_VIDEOS			}, // 
	{ "flv"				, IC_VIDEOS			}, // 
	{ "cast"			, IC_VIDEOS			}, // 
	{ "avi"				, IC_VIDEOS			}, // 
	{ "3gpp2"			, IC_VIDEOS			}, // 
	{ "3gpp"			, IC_VIDEOS			}, // 
	{ "3gp2"			, IC_VIDEOS			}, // 
	{ "3gp"				, IC_VIDEOS			}, // 
	{ "3g2"				, IC_VIDEOS			}, // 
	{ "suo"				, IC_VSCODE			}, // 
	{ "sln"				, IC_VSCODE			}, // 
	{ "prjpcb"			, IC_EDA_PCB		}, // 
	{ "pcbdoc"			, IC_EDA_PCB		}, // 
	{ "lpp"				, IC_EDA_PCB		}, // 
	{ "gts"				, IC_EDA_PCB		}, // 
	{ "gtp"				, IC_EDA_PCB		}, // 
	{ "gto"				, IC_EDA_PCB		}, // 
	{ "gtl"				, IC_EDA_PCB		}, // 
	{ "gml"				, IC_EDA_PCB		}, // 
	{ "gm1"				, IC_EDA_PCB		}, // 
	{ "gbs"				, IC_EDA_PCB		}, // 
	{ "gbr"				, IC_EDA_PCB		}, // 
	{ "gbp"				, IC_EDA_PCB		}, // 
	{ "gbo"				, IC_EDA_PCB		}, // 
	{ "gbl"				, IC_EDA_PCB		}, // 
	{ "brd"				, IC_EDA_PCB		}, // 
	{ "schdoc"			, IC_EDA_SCH		}, // 󰭅
	{ "sch"				, IC_EDA_SCH		}, // 󰭅
	{ "wrz"				, IC_FILE_3D		}, // 󰆧
	{ "wrl"				, IC_FILE_3D		}, // 󰆧
	{ "stl"				, IC_FILE_3D		}, // 󰆧
	{ "ply"				, IC_FILE_3D		}, // 󰆧
	{ "obj"				, IC_FILE_3D		}, // 󰆧
	{ "fbx"				, IC_FILE_3D		}, // 󰆧
	{ "3mf"				, IC_FILE_3D		}, // 󰆧
	{ "fctl"			, IC_FREECAD		}, // 
	{ "fctb"			, IC_FREECAD		}, // 
	{ "fcstd1"			, IC_FREECAD		}, // 
	{ "fcstd"			, IC_FREECAD		}, // 
	{ "fcscript"		, IC_FREECAD		}, // 
	{ "fcparam"			, IC_FREECAD		}, // 
	{ "fcmat"			, IC_FREECAD		}, // 
	{ "fcmacro"			, IC_FREECAD		}, // 
	{ "fcbak"			, IC_FREECAD		}, // 
	{ "graphql"			, IC_GRAPHQL		}, // 
	{ "gql"				, IC_GRAPHQL		}, // 
	{ "kdbx"			, IC_KEYPASS		}, // 
	{ "kdb"				, IC_KEYPASS		}, // 
	{ "go"				, IC_LANG_GO		}, // 
	{ "lib"				, IC_LIBRARY		}, // 
	{ "lbr"				, IC_LIBRARY		}, // 
	{ "dll"				, IC_LIBRARY		}, // 
	{ "license"			, IC_LICENSE		}, // 
	{ "service"			, IC_SERVICE		}, // 
	{ "sr"				, IC_SQ_WAVE		}, // 󱑻
	{ "sal"				, IC_SQ_WAVE		}, // 󱑻
	{ "sublime-theme"	, IC_SUBLIME		}, // 
	{ "sublime-snippet"	, IC_SUBLIME		}, // 
	{ "sublime-settings", IC_SUBLIME		}, // 
	{ "sublime-session"	, IC_SUBLIME		}, // 
	{ "sublime-project"	, IC_SUBLIME		}, // 
	{ "sublime-package"	, IC_SUBLIME		}, // 
	{ "sublime-options"	, IC_SUBLIME		}, // 
	{ "sublime-menu"	, IC_SUBLIME		}, // 
	{ "sublime-keymap"	, IC_SUBLIME		}, // 
	{ "sublime-build"	, IC_SUBLIME		}, // 
	{ "torrent"			, IC_TORRENT		}, // 
	{ "ifb"				, IC_CALENDAR		}, // 
	{ "ics"				, IC_CALENDAR		}, // 
	{ "icalendar"		, IC_CALENDAR		}, // 
	{ "ical"			, IC_CALENDAR		}, // 
	{ "sql"				, IC_DATABASE		}, // 
	{ "prql"			, IC_DATABASE		}, // 
	{ "odb"				, IC_DATABASE		}, // 
	{ "mdb"				, IC_DATABASE		}, // 
	{ "ldb"				, IC_DATABASE		}, // 
	{ "dump"			, IC_DATABASE		}, // 
	{ "dconf"			, IC_DATABASE		}, // 
	{ "db"				, IC_DATABASE		}, // 
	{ "gdoc"			, IC_DOCUMENT		}, // 
	{ "docx"			, IC_DOCUMENT		}, // 
	{ "docm"			, IC_DOCUMENT		}, // 
	{ "doc"				, IC_DOCUMENT		}, // 
	{ "djvu"			, IC_DOCUMENT		}, // 
	{ "djv"				, IC_DOCUMENT		}, // 
	{ "part"			, IC_DOWNLOAD		}, // 󰇚
	{ "fdmdownload"		, IC_DOWNLOAD		}, // 󰇚
	{ "download"		, IC_DOWNLOAD		}, // 󰇚
	{ "crdownload"		, IC_DOWNLOAD		}, // 󰇚
	{ "iml"				, IC_INTELLIJ		}, // 
	{ "kdenlivetitle"	, IC_KDENLIVE		}, // 
	{ "kdenlive"		, IC_KDENLIVE		}, // 
	{ "mm"				, IC_LANG_CPP		}, // 
	{ "hxx"				, IC_LANG_CPP		}, // 
	{ "hpp"				, IC_LANG_CPP		}, // 
	{ "hh"				, IC_LANG_CPP		}, // 
	{ "h++"				, IC_LANG_CPP		}, // 
	{ "cxx"				, IC_LANG_CPP		}, // 
	{ "cpp"				, IC_LANG_CPP		}, // 
	{ "cp"				, IC_LANG_CPP		}, // 
	{ "cc"				, IC_LANG_CPP		}, // 
	{ "c++"				, IC_LANG_CPP		}, // 
	{ "vhdl"			, IC_LANG_HDL		}, // 󰍛
	{ "svh"				, IC_LANG_HDL		}, // 󰍛
	{ "sv"				, IC_LANG_HDL		}, // 󰍛
	{ "luau"			, IC_LANG_LUA		}, // 
	{ "luac"			, IC_LANG_LUA		}, // 
	{ "lua"				, IC_LANG_LUA		}, // 
	{ "nims"			, IC_LANG_NIM		}, // 
	{ "nimble"			, IC_LANG_NIM		}, // 
	{ "nim"				, IC_LANG_NIM		}, // 
	{ "php"				, IC_LANG_PHP		}, // 
	{ "phar"			, IC_LANG_PHP		}, // 
	{ "tex"				, IC_LANG_TEX		}, // 
	{ "sty"				, IC_LANG_TEX		}, // 
	{ "ltx"				, IC_LANG_TEX		}, // 
	{ "latex"			, IC_LANG_TEX		}, // 
	{ "cls"				, IC_LANG_TEX		}, // 
	{ "bst"				, IC_LANG_TEX		}, // 
	{ "bib"				, IC_LANG_TEX		}, // 
	{ "rmd"				, IC_MARKDOWN		}, // 
	{ "rdoc"			, IC_MARKDOWN		}, // 
	{ "mkd"				, IC_MARKDOWN		}, // 
	{ "mdx"				, IC_MARKDOWN		}, // 
	{ "md"				, IC_MARKDOWN		}, // 
	{ "markdown"		, IC_MARKDOWN		}, // 
	{ "jmd"				, IC_MARKDOWN		}, // 
	{ "mustache"		, IC_MUSTACHE		}, // 
	{ "hbs"				, IC_MUSTACHE		}, // 
	{ "ipynb"			, IC_NOTEBOOK		}, // 
	{ "plist"			, IC_OS_APPLE		}, // 
	{ "localized"		, IC_OS_APPLE		}, // 
	{ "dylib"			, IC_OS_APPLE		}, // 
	{ "bundle"			, IC_OS_APPLE		}, // 
	{ "applescript"		, IC_OS_APPLE		}, // 
	{ "apple"			, IC_OS_APPLE		}, // 
	{ "so"				, IC_OS_LINUX		}, // 
	{ "ko"				, IC_OS_LINUX		}, // 
	{ "a"				, IC_OS_LINUX		}, // 
	{ "pls"				, IC_PLAYLIST		}, // 󰲹
	{ "m3u8"			, IC_PLAYLIST		}, // 󰲹
	{ "m3u"				, IC_PLAYLIST		}, // 󰲹
	{ "cue"				, IC_PLAYLIST		}, // 󰲹
	{ "sub"				, IC_SUBTITLE		}, // 󰨖
	{ "ssa"				, IC_SUBTITLE		}, // 󰨖
	{ "srt"				, IC_SUBTITLE		}, // 󰨖
	{ "sbt"				, IC_SUBTITLE		}, // 󰨖
	{ "lrc"				, IC_SUBTITLE		}, // 󰨖
	{ "ass"				, IC_SUBTITLE		}, // 󰨖
	{ "cljc"			, IC_CLOJURE_1		}, // 
	{ "clj"				, IC_CLOJURE_1		}, // 
	{ "edn"				, IC_CLOJURE_2		}, // 
	{ "cljs"			, IC_CLOJURE_2		}, // 
	{ "war"				, IC_LANG_JAVA		}, // 
	{ "java"			, IC_LANG_JAVA		}, // 
	{ "jar"				, IC_LANG_JAVA		}, // 
	{ "jad"				, IC_LANG_JAVA		}, // 
	{ "class"			, IC_LANG_JAVA		}, // 
	{ "t"				, IC_LANG_PERL		}, // 
	{ "pod"				, IC_LANG_PERL		}, // 
	{ "pm"				, IC_LANG_PERL		}, // 
	{ "plx"				, IC_LANG_PERL		}, // 
	{ "pl"				, IC_LANG_PERL		}, // 
	{ "ru"				, IC_LANG_RUBY		}, // 
	{ "rspec_status"	, IC_LANG_RUBY		}, // 
	{ "rspec_parallel"	, IC_LANG_RUBY		}, // 
	{ "rspec"			, IC_LANG_RUBY		}, // 
	{ "rb"				, IC_LANG_RUBY		}, // 
	{ "rakefile"		, IC_LANG_RUBY		}, // 
	{ "rake"			, IC_LANG_RUBY		}, // 
	{ "procfile"		, IC_LANG_RUBY		}, // 
	{ "guardfile"		, IC_LANG_RUBY		}, // 
	{ "gemspec"			, IC_LANG_RUBY		}, // 
	{ "gemfile"			, IC_LANG_RUBY		}, // 
	{ "gem"				, IC_LANG_RUBY		}, // 
	{ "rs"				, IC_LANG_RUST		}, // 
	{ "rmeta"			, IC_LANG_RUST		}, // 
	{ "rlib"			, IC_LANG_RUST		}, // 
	{ "scss"			, IC_LANG_SASS		}, // 
	{ "sass"			, IC_LANG_SASS		}, // 
	{ "psd"				, IC_PHOTOSHOP		}, // 
	{ "psb"				, IC_PHOTOSHOP		}, // 
	{ "zsh"				, IC_SHELL_CMD		}, // 
	{ "shell"			, IC_SHELL_CMD		}, // 
	{ "sh"				, IC_SHELL_CMD		}, // 
	{ "nu"				, IC_SHELL_CMD		}, // 
	{ "ksh"				, IC_SHELL_CMD		}, // 
	{ "fish"			, IC_SHELL_CMD		}, // 
	{ "csh"				, IC_SHELL_CMD		}, // 
	{ "bats"			, IC_SHELL_CMD		}, // 
	{ "bash"			, IC_SHELL_CMD		}, // 
	{ "awk"				, IC_SHELL_CMD		}, // 
	{ "tfvars"			, IC_TERRAFORM		}, // 󱁢
	{ "tfstate"			, IC_TERRAFORM		}, // 󱁢
	{ "tf"				, IC_TERRAFORM		}, // 󱁢
	{ "sfz"				, IC_TREB_CLEF		}, // 󰽰
	{ "sf2"				, IC_TREB_CLEF		}, // 󰽰
	{ "zst"				, IC_COMPRESSED		}, // 
	{ "zip"				, IC_COMPRESSED		}, // 
	{ "z"				, IC_COMPRESSED		}, // 
	{ "xz"				, IC_COMPRESSED		}, // 
	{ "tzo"				, IC_COMPRESSED		}, // 
	{ "tz"				, IC_COMPRESSED		}, // 
	{ "txz"				, IC_COMPRESSED		}, // 
	{ "tlz"				, IC_COMPRESSED		}, // 
	{ "tgz"				, IC_COMPRESSED		}, // 
	{ "tbz2"			, IC_COMPRESSED		}, // 
	{ "tbz"				, IC_COMPRESSED		}, // 
	{ "taz"				, IC_COMPRESSED		}, // 
	{ "tar"				, IC_COMPRESSED		}, // 
	{ "rar"				, IC_COMPRESSED		}, // 
	{ "par"				, IC_COMPRESSED		}, // 
	{ "lzo"				, IC_COMPRESSED		}, // 
	{ "lzma"			, IC_COMPRESSED		}, // 
	{ "lzh"				, IC_COMPRESSED		}, // 
	{ "lz4"				, IC_COMPRESSED		}, // 
	{ "lz"				, IC_COMPRESSED		}, // 
	{ "gz"				, IC_COMPRESSED		}, // 
	{ "cpio"			, IC_COMPRESSED		}, // 
	{ "bz3"				, IC_COMPRESSED		}, // 
	{ "bz2"				, IC_COMPRESSED		}, // 
	{ "bz"				, IC_COMPRESSED		}, // 
	{ "br"				, IC_COMPRESSED		}, // 
	{ "arj"				, IC_COMPRESSED		}, // 
	{ "ar"				, IC_COMPRESSED		}, // 
	{ "7z"				, IC_COMPRESSED		}, // 
	{ "vmdk"			, IC_DISK_IMAGE		}, // 
	{ "vhd"				, IC_DISK_IMAGE		}, // 
	{ "vdi"				, IC_DISK_IMAGE		}, // 
	{ "tc"				, IC_DISK_IMAGE		}, // 
	{ "qcow2"			, IC_DISK_IMAGE		}, // 
	{ "qcow"			, IC_DISK_IMAGE		}, // 
	{ "iso"				, IC_DISK_IMAGE		}, // 
	{ "img"				, IC_DISK_IMAGE		}, // 
	{ "image"			, IC_DISK_IMAGE		}, // 
	{ "dmg"				, IC_DISK_IMAGE		}, // 
	{ "gleam"			, IC_LANG_GLEAM		}, // 󰦥
	{ "hc"				, IC_LANG_HOLYC		}, // 󰂢
	{ "mjs"				, IC_LANG_JSCPT		}, // 
	{ "js"				, IC_LANG_JSCPT		}, // 
	{ "cjs"				, IC_LANG_JSCPT		}, // 
	{ "mly"				, IC_LANG_OCAML		}, // 
	{ "mll"				, IC_LANG_OCAML		}, // 
	{ "mli"				, IC_LANG_OCAML		}, // 
	{ "ml"				, IC_LANG_OCAML		}, // 
	{ "ts"				, IC_LANG_TSCPT		}, // 
	{ "mts"				, IC_LANG_TSCPT		}, // 
	{ "cts"				, IC_LANG_TSCPT		}, // 
	{ "apk"				, IC_OS_ANDROID		}, // 
	{ "android"			, IC_OS_ANDROID		}, // 
	{ "windows"			, IC_OS_WINDOWS		}, // 
	{ "msi"				, IC_OS_WINDOWS		}, // 
	{ "cmd"				, IC_OS_WINDOWS		}, // 
	{ "cab"				, IC_OS_WINDOWS		}, // 
	{ "psm1"			, IC_POWERSHELL		}, // 
	{ "psd1"			, IC_POWERSHELL		}, // 
	{ "ps1"				, IC_POWERSHELL		}, // 
	{ "pub"				, IC_PUBLIC_KEY		}, // 󰷖
	{ "kbx"				, IC_SHIELD_KEY		}, // 󰯄
	{ "bak"				, IC_BACKUP_FILE	}, // 󰁯  – JV
	{ "desktop"			, IC_DESKTOP_EXT	}, // 
	{ "crt"				, IC_GIST_SECRET	}, // 
	{ "cert"			, IC_GIST_SECRET	}, // 
	{ "csx"				, IC_LANG_CSHARP	}, // 󰌛
	{ "csproj"			, IC_LANG_CSHARP	}, // 󰌛
	{ "cs"				, IC_LANG_CSHARP	}, // 󰌛
	{ "leex"			, IC_LANG_ELIXIR	}, // 
	{ "exs"				, IC_LANG_ELIXIR	}, // 
	{ "ex"				, IC_LANG_ELIXIR	}, // 
	{ "eex"				, IC_LANG_ELIXIR	}, // 
	{ "fnl"				, IC_LANG_FENNEL	}, // 
	{ "fsx"				, IC_LANG_FSHARP	}, // 
	{ "fsscript"		, IC_LANG_FSHARP	}, // 
	{ "fsproj"			, IC_LANG_FSHARP	}, // 
	{ "fsi"				, IC_LANG_FSHARP	}, // 
	{ "fs"				, IC_LANG_FSHARP	}, // 
	{ "f#"				, IC_LANG_FSHARP	}, // 
	{ "gvy"				, IC_LANG_GROOVY	}, // 
	{ "groovy"			, IC_LANG_GROOVY	}, // 
	{ "kts"				, IC_LANG_KOTLIN	}, // 
	{ "kt"				, IC_LANG_KOTLIN	}, // 
	{ "whl"				, IC_LANG_PYTHON	}, // 
	{ "pyx"				, IC_LANG_PYTHON	}, // 
	{ "pyw"				, IC_LANG_PYTHON	}, // 
	{ "pyo"				, IC_LANG_PYTHON	}, // 
	{ "pyi"				, IC_LANG_PYTHON	}, // 
	{ "pyd"				, IC_LANG_PYTHON	}, // 
	{ "pyc"				, IC_LANG_PYTHON	}, // 
	{ "py"				, IC_LANG_PYTHON	}, // 
	{ "pxd"				, IC_LANG_PYTHON	}, // 
	{ "ss"				, IC_LANG_SCHEME	}, // 
	{ "sld"				, IC_LANG_SCHEME	}, // 
	{ "scm"				, IC_LANG_SCHEME	}, // 
	{ "rkt"				, IC_LANG_SCHEME	}, // 
	{ "stylus"			, IC_LANG_STYLUS	}, // 
	{ "styl"			, IC_LANG_STYLUS	}, // 
	{ "gpg"				, IC_SHIELD_LOCK	}, // 󰦝
	{ "asc"				, IC_SHIELD_LOCK	}, // 󰦝
	{ "age"				, IC_SHIELD_LOCK	}, // 󰦝
	{ "signature"		, IC_SIGNED_FILE	}, // 󱧃
	{ "sig"				, IC_SIGNED_FILE	}, // 󱧃
	{ "qm"				, IC_TRANSLATION	}, // 󰗊
	{ "pot"				, IC_TRANSLATION	}, // 󰗊
	{ "po"				, IC_TRANSLATION	}, // 󰗊
	{ "mo"				, IC_TRANSLATION	}, // 󰗊
	{ "editorconfig"	, IC_EDITORCONFIG	}, // 
	{ "ino"				, IC_LANG_ARDUINO	}, // 
	{ "for"				, IC_LANG_FORTRAN	}, // 󱈚
	{ "f90"				, IC_LANG_FORTRAN	}, // 󱈚
	{ "f"				, IC_LANG_FORTRAN	}, // 󱈚
	{ "lhs"				, IC_LANG_HASKELL	}, // 
	{ "hs"				, IC_LANG_HASKELL	}, // 
	{ "slim"			, IC_LANG_RBRAILS	}, // 
	{ "rubydoc"			, IC_LANG_RBRAILS	}, // 
	{ "erb"				, IC_LANG_RBRAILS	}, // 
	{ "sha512"			, IC_SHIELD_CHECK	}, // 󰕥
	{ "sha384"			, IC_SHIELD_CHECK	}, // 󰕥
	{ "sha256"			, IC_SHIELD_CHECK	}, // 󰕥
	{ "sha224"			, IC_SHIELD_CHECK	}, // 󰕥
	{ "sha1"			, IC_SHIELD_CHECK	}, // 󰕥
	{ "md5"				, IC_SHIELD_CHECK	}, // 󰕥
	{ "s"				, IC_LANG_ASSEMBLY	}, // 
	{ "asm"				, IC_LANG_ASSEMBLY	}, // 
	{ "exe"				, IC_OS_WINDOWS_CMD	}, // 
	{ "bat"				, IC_OS_WINDOWS_CMD	}, // 
	END_OF_ICONS
};

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignoreRegexp /((?<=\bIC_)\w+|(?<=\{[ \t]+")[\w-.]+(?=")/g
