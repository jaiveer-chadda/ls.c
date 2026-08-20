/// @file icons/definitions.c

#include "icons.h"

/* —— Base Icon Definitions ———————————————————————————————————————————————————————————————————————————————————————— */

#define IC_FILE				L''
#define IC_FILE_UNKNOWN		L'󰡯'

#define IC_FOLDER			L''
#define IC_FOLDER_OPEN		L''

#define IC_ACF				L''
#define IC_AI				L''
#define IC_APP				L'' // — JV
#define IC_APPLICATIONS		L'' // — JV
#define IC_ARCHBTW			L''
#define IC_ARCHIVE			L'󱝏' // — JV
#define IC_ASP				L''
#define IC_ATOM				L''
#define IC_AUDIO			L''
#define IC_BACKUP_DIR		L'󰴋' // — JV
#define IC_BACKUP_FILE		L'󰁯' // — JV
#define IC_BASH				L'' // — JV
#define IC_BINARY			L'' // — JV
#define IC_BLEND			L'󰂫'
#define IC_BOOK				L''
#define IC_BSPWM			L''
#define IC_BUILDING			L'󱔟' // — JV
#define IC_BUN				L''
#define IC_CACHE			L''
#define IC_CAD				L'󰻫'
#define IC_CALENDAR			L''
#define IC_CAMERA			L'󰄀' // — JV
#define IC_CAR				L'󰞬' // — JV
#define IC_CHIP				L'' // — JV
#define IC_CLOCK			L''
#define IC_CLOJURE_1		L''
#define IC_CLOJURE_2		L''
#define IC_CMAKE			L''
#define IC_CODE_OF_CONDUCT	L''
#define IC_CODESPELL		L'󰓆'
#define IC_COFFEE			L''
#define IC_COM				L''
#define IC_COMPRESSED		L''
#define IC_CONDA			L''
#define IC_CONFIG			L'󱁻'
#define IC_CONTACTS			L'󰉌'
#define IC_COREDUMP			L'' // — JV
#define IC_COW				L'󰆚'
#define IC_CR				L''
#define IC_CROWN			L'' // — JV
#define IC_CSS3				L''
#define IC_CSV				L''
#define IC_CU				L''
#define IC_DART				L''
#define IC_DATABASE			L''
#define IC_DEB				L''
#define IC_DEBUG			L'' // — JV
#define IC_DESKTOP			L''
#define IC_DESKTOP_EXT		L''
#define IC_DEVICES			L'󰾰' // — JV
#define IC_DIFF				L''
#define IC_DISCORD			L'' // — JV
#define IC_DISK_IMAGE		L''
#define IC_DOCKER			L''
#define IC_DOCUMENT			L''
#define IC_DOCUMENTS		L'󰲂'
#define IC_DOWNLOAD			L'󰇚'
#define IC_DOWNLOADS		L'󰉍'
#define IC_DRAWIO			L''
#define IC_DROPBOX			L''
#define IC_EARTH			L''
#define IC_EBUILD			L''
#define IC_EDA_PCB			L''
#define IC_EDA_SCH			L'󰭅'
#define IC_EDITORCONFIG		L''
#define IC_EJS				L''
#define IC_ELM				L''
#define IC_EMACS			L''
#define IC_EML				L''
#define IC_ENV				L''
#define IC_ERLANG			L''
#define IC_ESLINT			L''
#define IC_EXERCISM			L''
#define IC_EZA				L'󰉻' // — JV
#define IC_FAVORITES		L'󰚝'
#define IC_FILE_3D			L'󰆧'
#define IC_FILEPATHS		L'' // — JV
#define IC_FISH				L'' // — JV
#define IC_FLAKE			L''
#define IC_FOLDER_BUILD		L'󱧼'
#define IC_FOLDER_CONFIG	L''
#define IC_FOLDER_GIT		L''
#define IC_FOLDER_GITHUB	L''
#define IC_FOLDER_HIDDEN	L'󱞞'
#define IC_FOLDER_KEY		L'󰢬'
#define IC_FOLDER_NPM		L''
#define IC_FONT				L''
#define IC_FONTFORGE		L'' // — JV
#define IC_FREECAD			L''
#define IC_FUNCTIONS		L'󰡱' // — JV
#define IC_GBA				L'󱎓'
#define IC_GCODE			L'󰫴'
#define IC_GEAR				L'' // — JV
#define IC_GEM				L'' // — JV
#define IC_GFORM			L''
#define IC_GIMP				L''
#define IC_GIST_SECRET		L''
#define IC_GIT				L'󰊢'
#define IC_GITLAB			L''
#define IC_GODOT			L''
#define IC_GOOGLE_CLOUD		L'󱇶'
#define IC_GRAD_CAP			L'' // — JV
#define IC_GRADLE			L''
#define IC_GRAPH			L'󱁉'
#define IC_GRAPHQL			L''
#define IC_GRUNT			L''
#define IC_GTK				L''
#define IC_GULP				L''
#define IC_HAML				L''
#define IC_HAMMER			L'󰣪' // — JV
#define IC_HEROKU			L''
#define IC_HEX				L'󱊧'
#define IC_HOME				L'󱂵'
#define IC_HOMEBREW			L'󱄖'
#define IC_HOOK				L'󰛢'
#define IC_HTML5			L''
#define IC_HYPRLAND			L''
#define IC_I3				L''
#define IC_IMAGE			L''
#define IC_INFO				L''
#define IC_INTELLIJ			L''
#define IC_ITERM2			L'' // — JV
#define IC_JENKINSFILE		L''
#define IC_JL				L''
#define IC_JSON				L''
#define IC_JUPYTER			L'' // — JV
#define IC_JV				L'↧' // — JV
#define IC_JWMRC			L''
#define IC_KDE				L''
#define IC_KDENLIVE			L''
#define IC_KEY				L''
#define IC_KEYBOARD			L'' // — JV
#define IC_KEYPASS			L''
#define IC_KICAD			L''
#define IC_KRITA			L''
#define IC_LANG_ARDUINO		L''
#define IC_LANG_ASSEMBLY	L''
#define IC_LANG_C			L''
#define IC_LANG_C_HEADER	L'' // — JV
#define IC_LANG_CPP			L''
#define IC_LANG_CSHARP		L'󰌛'
#define IC_LANG_D			L''
#define IC_LANG_ELIXIR		L''
#define IC_LANG_FENNEL		L''
#define IC_LANG_FORTRAN		L'󱈚'
#define IC_LANG_FSHARP		L''
#define IC_LANG_GLEAM		L'󰦥'
#define IC_LANG_GO			L''
#define IC_LANG_GROOVY		L''
#define IC_LANG_HASKELL		L''
#define IC_LANG_HDL			L'󰍛'
#define IC_LANG_HOLYC		L'󰂢'
#define IC_LANG_JAVA		L''
#define IC_LANG_JSCPT		L''
#define IC_LANG_KOTLIN		L''
#define IC_LANG_LUA			L''
#define IC_LANG_NIM			L''
#define IC_LANG_OCAML		L''
#define IC_LANG_PERL		L''
#define IC_LANG_PHP			L''
#define IC_LANG_PYTHON		L''
#define IC_LANG_R			L''
#define IC_LANG_RBRAILS		L''
#define IC_LANG_RUBY		L''
#define IC_LANG_RUST		L''
#define IC_LANG_SASS		L''
#define IC_LANG_SCHEME		L''
#define IC_LANG_SHELL		L'' // — JV
#define IC_LANG_STYLUS		L''
#define IC_LANG_TEX			L''
#define IC_LANG_TSCPT		L''
#define IC_LANG_V			L''
#define IC_LAPTOP			L'' // — JV
#define IC_LESS				L''
#define IC_LIBRARY			L'' // — JV
#define IC_LICENSE			L''
#define IC_LINEARMOUSE		L'󰍽' // — JV
#define IC_LISP				L'󰅲'
#define IC_LOCK				L''
#define IC_LOG				L''
#define IC_LXDE				L''
#define IC_LXQT				L''
#define IC_MAGNET			L''
#define IC_MAIL				L'󰇰'
#define IC_MAKE				L''
#define IC_MAN_PAGES		L'󰺄' // — JV
#define IC_MARKDOWN			L''
#define IC_MID				L'󰣲'
#define IC_MOVIES			L'󰿎'
#define IC_MPV				L''
#define IC_MSF				L''
#define IC_MUSIC			L'󱍙'
#define IC_MUSTACHE			L''
#define IC_NANO				L''
#define IC_NEOFETCH			L'󱥈' // — JV
#define IC_NEWS				L''
#define IC_NINJA			L'󰝴'
#define IC_NODEJS			L''
#define IC_NOFOLLOW			L'' // — JV
#define IC_NORG				L''
#define IC_NOTEBOOK			L''
#define IC_NOTES			L'' // — JV
#define IC_NPM				L''
#define IC_NUXT				L'󱄆'
#define IC_NVM				L'' // — JV
#define IC_ODF				L''
#define IC_ODG				L''
#define IC_ODP				L''
#define IC_ODS				L''
#define IC_ODT				L''
#define IC_OPAM				L'󰘧'
#define IC_OPT				L'' // — JV
#define IC_ORG				L''
#define IC_OS_ANDROID		L''
#define IC_OS_APPLE			L''
#define IC_OS_LINUX			L''
#define IC_OS_WINDOWS		L''
#define IC_OS_WINDOWS_CMD	L''
#define IC_OUT				L''
#define IC_PAINTBRUSH		L''
#define IC_PDF				L''
#define IC_PEOPLE			L''
#define IC_PHOTOSHOP		L''
#define IC_PICTURES			L'󰉏'
#define IC_PIP				L'' // — JV
#define IC_PIPES			L'󰟥' // — JV
#define IC_PKG				L''
#define IC_PLATFORMIO		L''
#define IC_PLAYLIST			L'󰲹'
#define IC_POM				L''
#define IC_POWERSHELL		L''
#define IC_PP				L''
#define IC_PRETTIER			L''
#define IC_PRIVATE_KEY		L'󰌆'
#define IC_PRUSASLICER		L''
#define IC_PUBLIC			L'󰛍' // — JV
#define IC_PUBLIC_KEY		L'󰷖'
#define IC_PURS				L''
#define IC_QT				L''
#define IC_RAYCAST			L'' // — JV
#define IC_RAZOR			L''
#define IC_RDB				L''
#define IC_REACT			L''
#define IC_README			L'󰂺'
#define IC_RENOVATE			L'󰉼'
#define IC_RESOLVE			L'󰕟' // — JV
#define IC_RESOURCES		L'󱂸' // — JV
#define IC_ROBOT			L'󰚩'
#define IC_ROSE				L'󰧲' // — JV
#define IC_RPM				L''
#define IC_RSS				L''
#define IC_SCAD				L''
#define IC_SCALA			L''
#define IC_SECURITY			L'󰒃'
#define IC_SERVICE			L''
#define IC_SHARED			L'󱒃' // — JV
#define IC_SHEET			L''
#define IC_SHELL			L'󱆃'
#define IC_SHELL_CMD		L''
#define IC_SHIELD_CHECK		L'󰕥'
#define IC_SHIELD_KEY		L'󰯄'
#define IC_SHIELD_LOCK		L'󰦝'
#define IC_SHIP				L'' // — JV
#define IC_SIGNED_FILE		L'󱧃'
#define IC_SLIDE			L''
#define IC_SPOTIFY			L'' // — JV
#define IC_SQ_WAVE			L'󱑻'
#define IC_SQLITE			L''
#define IC_SRC				L'󰣞'
#define IC_SSH_LOGO			L'󰣀'
#define IC_STAR				L''
#define IC_STOW				L''
#define IC_SUBLIME			L''
#define IC_SUBTITLE			L'󰨖'
#define IC_SVELTE			L''
#define IC_SVN				L'' // — JV
#define IC_SWIFT			L'' // — JV
#define IC_SWITCH			L'󰟡'
#define IC_SYSTEM			L'󰡀' // — JV
#define IC_TCL				L'󰛓'
#define IC_TEMP				L'󰔛' // — JV
#define IC_TERRAFORM		L'󱁢'
#define IC_TEXT				L''
#define IC_TMUX				L''
#define IC_TODO				L''
#define IC_TOML				L''
#define IC_TOP				L'󰨇' // — JV
#define IC_TORRENT			L''
#define IC_TRANSLATION		L'󰗊'
#define IC_TRASH			L''
#define IC_TREB_CLEF		L'󰽰'
#define IC_TWIG				L''
#define IC_TYPST			L''
#define IC_UI				L''
#define IC_UNITY			L''
#define IC_USER				L'' // — JV
#define IC_USERS			L'' // — JV
#define IC_VAGRANT			L'⍱'
#define IC_VALA				L''
#define IC_VAR				L'󰫧' // — JV
#define IC_VECTOR			L'󰕙'
#define IC_VHS				L'󰨛'
#define IC_VI				L''
#define IC_VIDEOS			L''
#define IC_VIM				L''
#define IC_VLC				L'󰕼'
#define IC_VOLUME			L'󰥠' // — JV
#define IC_VPN				L'󰲝' // — JV
#define IC_VSC_SHARED		L'' // — JV
#define IC_VSCODE			L''
#define IC_VSIX				L'󰨞'
#define IC_VUE				L'󰡄'
#define IC_WEB				L'󰖟' // — JV
#define IC_WEBPACK			L'󰜫'
#define IC_WESTON			L''
#define IC_WRENCH			L''
#define IC_XAML				L'󰙳'
#define IC_XML				L'󰗀'
#define IC_XORG				L''
#define IC_XPI				L''
#define IC_YAML				L''
#define IC_YARN				L''
#define IC_ZIG				L''

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— Default Icons ———————————————————————————————————————————————————————————————————————————————————————————————— */

const icon_t DEFAULT_FILE_ICON = IC_FILE;
const icon_t UNKNOWN_EXT_ICON  = IC_FILE_UNKNOWN;
const icon_t DEFAULT_DIR_ICON  = IC_FOLDER;

/* —— Directory Icons —————————————————————————————————————————————————————————————————————————————————————————————— */

/// An array containing the basenames of directories, and their associated icons.
/// This array should contain all the directories that have custom icons.
const Icon DIRNAME_ICONS[] = {
	{ "__filepaths__"	, IC_FILEPATHS 		}, //   – JV
	{ ".archive"		, IC_ARCHIVE 		}, // 󱝏  – JV
	{ ".cache"			, IC_CACHE 			}, //   – JV
	{ ".config"			, IC_GEAR			}, //   – JV
	{ ".exercism"		, IC_EXERCISM		}, // 
	{ ".git"			, IC_FOLDER_GIT		}, // 󰊢  – JV
	{ ".github"			, IC_FOLDER_GITHUB	}, // 
	{ ".history"		, IC_CLOCK 			}, //   – JV
	{ ".idea"			, IC_INTELLIJ		}, //   – JV
	{ ".local"			, IC_LAPTOP 		}, //   – JV
	{ ".nofollow"		, IC_NOFOLLOW		}, //   – JV
	{ ".npm"			, IC_FOLDER_NPM		}, // 
	{ ".opam"			, IC_LANG_OCAML		}, // 
	{ ".resolve"		, IC_RESOLVE 		}, // 󰕟  – JV
	{ ".ssh"			, IC_FOLDER_KEY		}, // 󰢬
	{ ".swiftpm"		, IC_SWIFT 			}, //   – JV
	{ ".trash"			, IC_TRASH			}, // 
	{ ".vol"			, IC_VOLUME 		}, // 󰥠  – JV
	{ ".vscode-shared"	, IC_VSC_SHARED 	}, //   – JV
	{ ".vscode"			, IC_VSCODE 		}, //   – JV
	{ "anaconda"		, IC_CONDA 			}, //   – JV
	{ "applescript"		, IC_OS_APPLE 		}, //   – JV
	{ "applications"	, IC_APPLICATIONS	}, //   – JV
	{ "apps"			, IC_APPLICATIONS	}, //   – JV
	{ "archive"			, IC_ARCHIVE		}, // 󱝏  – JV
	{ "archives"		, IC_ARCHIVE		}, // 󱝏  – JV
	{ "bash"			, IC_BASH 			}, //   – JV
	{ "bin"				, IC_BINARY			}, //   – JV
	{ "bottom"			, IC_TOP 			}, // 󰨇  – JV
	{ "bpytop"			, IC_TOP 			}, // 󰨇  – JV
	{ "brew"			, IC_HOMEBREW 		}, // 󱄖  – JV
	{ "build"			, IC_FOLDER_BUILD	}, // 󱧼
	{ "c"				, IC_LANG_C 		}, //   – JV
	{ "c#"				, IC_LANG_CSHARP 	}, // 󰌛  – JV
	{ "cabal"			, IC_LANG_HASKELL	}, // 
	{ "cargo"			, IC_LANG_RUST 		}, //   – JV
	{ "conda"			, IC_CONDA 			}, //   – JV
	{ "config"			, IC_FOLDER_CONFIG	}, // 
	{ "configstore"		, IC_GEAR 			}, //   – JV
	{ "contacts"		, IC_CONTACTS		}, // 󰉌
	{ "cores"			, IC_COREDUMP 		}, //   – JV
	{ "cron.d"			, IC_FOLDER_CONFIG	}, // 
	{ "cron.daily"		, IC_FOLDER_CONFIG	}, // 
	{ "cron.hourly"		, IC_FOLDER_CONFIG	}, // 
	{ "cron.minutely"	, IC_FOLDER_CONFIG	}, // 
	{ "cron.monthly"	, IC_FOLDER_CONFIG	}, // 
	{ "cron.weekly"		, IC_FOLDER_CONFIG	}, // 
	{ "cs"				, IC_CHIP 			}, //   – JV
	{ "debug"			, IC_DEBUG 			}, //   – JV
	{ "debugging"		, IC_DEBUG 			}, //   – JV
	{ "desktop"			, IC_DESKTOP		}, // 
	{ "dev"				, IC_DEVICES 		}, // 󰾰  – JV
	{ "discord"			, IC_DISCORD 		}, //   – JV
	{ "documents"		, IC_DOCUMENTS		}, // 󰲂
	{ "downloads"		, IC_DOWNLOADS		}, // 󰉍
	{ "etc"				, IC_FOLDER_CONFIG	}, // 
	{ "expressvpn"		, IC_VPN 			}, // 󰲝  – JV
	{ "ey"				, IC_BUILDING 		}, // 󱔟  – JV
	{ "eza"				, IC_EZA 			}, // 󰉻  – JV
	{ "favorites"		, IC_FAVORITES		}, // 󰚝
	{ "fish"			, IC_FISH 			}, //   – JV
	{ "fontforge"		, IC_FONTFORGE 		}, //   – JV
	{ "functions"		, IC_FUNCTIONS 		}, // 󰡱  – JV
	{ "gem"				, IC_GEM 			}, //   – JV
	{ "gh"				, IC_GIT 			}, // 󰊢  – JV
	{ "git"				, IC_GIT 			}, // 󰊢  – JV
	{ "hdd"				, IC_VOLUME 		}, // 󰥠  – JV
	{ "hidden"			, IC_FOLDER_HIDDEN	}, // 󱞞
	{ "home"			, IC_HOME			}, // 󱂵
	{ "homebrew"		, IC_HOMEBREW 		}, // 󱄖  – JV
	{ "house of lords"	, IC_CROWN 			}, //   – JV
	{ "htop"			, IC_TOP 			}, // 󰨇  – JV
	{ "include"			, IC_FOLDER_CONFIG	}, // 
	{ "ipython"			, IC_LANG_PYTHON 	}, //   – JV
	{ "iterm2"			, IC_ITERM2 		}, //   – JV
	{ "java"			, IC_LANG_JAVA 		}, //   – JV
	{ "jgit"			, IC_GIT 			}, // 󰊢  – JV
	{ "jupyter"			, IC_JUPYTER 		}, //   – JV
	{ "jv"				, IC_JV				}, // ↧  – JV
	{ "karabiner"		, IC_KEYBOARD 		}, //   – JV
	{ "labour"			, IC_ROSE 			}, // 󰧲  – JV
	{ "lazygit"			, IC_GIT 			}, // 󰊢  – JV
	{ "lib"				, IC_LIBRARY 		}, //   – JV
	{ "library"			, IC_LIBRARY 		}, //   – JV
	{ "linearmouse"		, IC_LINEARMOUSE 	}, // 󰍽  – JV
	{ "mail"			, IC_MAIL			}, // 󰇰
	{ "man pages"		, IC_MAN_PAGES 		}, // 󰺄  – JV
	{ "mclaren"			, IC_CAR 			}, // 󰞬  – JV
	{ "movies"			, IC_MOVIES			}, // 󰿎
	{ "music"			, IC_MUSIC			}, // 󱍙
	{ "neofetch"		, IC_NEOFETCH 		}, // 󱥈  – JV
	{ "node_modules"	, IC_FOLDER_NPM		}, // 
	{ "notes"			, IC_NOTES 			}, //   – JV
	{ "npm_cache"		, IC_FOLDER_NPM		}, // 
	{ "npm"				, IC_FOLDER_NPM 	}, //   – JV
	{ "nvim"			, IC_VIM 			}, //   – JV
	{ "nvm"				, IC_NVM 			}, //   – JV
	{ "old desktop"		, IC_DESKTOP 		}, //   – JV
	{ "opt"				, IC_OPT 			}, //   – JV
	{ "out"				, IC_FOLDER_BUILD	}, // 󱧼  – JV
	{ "pacman.d"		, IC_FOLDER_CONFIG	}, // 
	{ "pam.d"			, IC_FOLDER_KEY		}, // 󰢬
	{ "pictures"		, IC_PICTURES		}, // 󰉏
	{ "pip"				, IC_PIP 			}, //   – JV
	{ "pipes-rs"		, IC_PIPES 			}, // 󰟥  – JV
	{ "powershell"		, IC_POWERSHELL 	}, //   – JV
	{ "private"			, IC_LOCK			}, //   – JV
	{ "public"			, IC_PUBLIC 		}, // 󰛍  – JV
	{ "python"			, IC_LANG_PYTHON 	}, //   – JV
	{ "ra"				, IC_HAMMER 		}, // 󰣪  – JV
	{ "raycast"			, IC_RAYCAST 		}, //   – JV
	{ "rdoc"			, IC_LANG_RUBY 		}, //   – JV
	{ "resources"		, IC_RESOURCES		}, // 󱂸  – JV
	{ "rn"				, IC_SHIP 			}, //   – JV
	{ "rust"			, IC_LANG_RUST 		}, //   – JV
	{ "rustup"			, IC_LANG_RUST 		}, //   – JV
	{ "sbin"			, IC_BINARY			}, //   – JV
	{ "screenshots"		, IC_CAMERA 		}, // 󰄀  – JV
	{ "shared"			, IC_SHARED 		}, // 󱒃  – JV
	{ "shellscript"		, IC_LANG_SHELL 	}, //   – JV
	{ "shpotify"		, IC_SPOTIFY 		}, //   – JV
	{ "source"			, IC_SRC			}, // 󰣞  – JV
	{ "spicetify"		, IC_SPOTIFY 		}, //   – JV
	{ "spotify-player"	, IC_SPOTIFY 		}, //   – JV
	{ "src"				, IC_SRC			}, // 󰣞
	{ "ssh"				, IC_FOLDER_KEY		}, // 󰢬
	{ "sudoers.d"		, IC_FOLDER_KEY		}, // 󰢬
	{ "svn"				, IC_SVN 			}, //   – JV
	{ "swift"			, IC_SWIFT 			}, //   – JV
	{ "system"			, IC_SYSTEM 		}, // 󰡀  – JV
	{ "tmp"				, IC_TEMP 			}, // 󰔛  – JV
	{ "university work"	, IC_GRAD_CAP 		}, //   – JV
	{ "users"			, IC_USERS 			}, //   – JV
	{ "usr"				, IC_USER 			}, //   – JV
	{ "var"				, IC_VAR 			}, // 󰫧  – JV
	{ "videos"			, IC_VIDEOS			}, // 
	{ "vim"				, IC_VIM 			}, //   – JV
	{ "volumes"			, IC_VOLUME 		}, // 󰥠  – JV
	{ "vs_code"			, IC_VSCODE 		}, //   – JV
	{ "vscode-custom"	, IC_VSCODE 		}, //   – JV
	{ "web"				, IC_WEB 			}, // 󰖟  – JV
	{ "x_automation"	, IC_ROBOT 			}, // 󰚩  – JV
	{ "xbps.d"			, IC_FOLDER_CONFIG	}, // 
	{ "xorg.conf.d"		, IC_FOLDER_CONFIG	}, // 
	{ "y_settings_etc"	, IC_GEAR 			}, //   – JV
	{ "z_other"			, IC_ARCHIVE 		}, // 󱝏  – JV
	{ "zsh"				, IC_SHELL_CMD 		}, //   – JV
	END_OF_ICONS
};

/* —— Filename Icons ——————————————————————————————————————————————————————————————————————————————————————————————— */

/// Array containing full filenames & their icons.
const Icon FILENAME_ICONS[] = {
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
	{ ".localized"					, IC_TRANSLATION		}, // 󰗊  — JV
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
	{ ".VolumeIcon.icns"			, IC_IMAGE				}, // •  — JV
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
	{ "hdd"							, IC_VOLUME 			}, // 󰥠  — JV
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
	{ "123dx"			, IC_CAD			}, // 󰻫
	{ "3dm"				, IC_CAD			}, // 󰻫
	{ "3g2"				, IC_VIDEOS			}, // 
	{ "3gp"				, IC_VIDEOS			}, // 
	{ "3gp2"			, IC_VIDEOS			}, // 
	{ "3gpp"			, IC_VIDEOS			}, // 
	{ "3gpp2"			, IC_VIDEOS			}, // 
	{ "3mf"				, IC_FILE_3D		}, // 󰆧
	{ "7z"				, IC_COMPRESSED		}, // 
	{ "a"				, IC_OS_LINUX		}, // 
	{ "aac"				, IC_AUDIO			}, // 
	{ "acf"				, IC_ACF			}, // 
	{ "age"				, IC_SHIELD_LOCK	}, // 󰦝
	{ "ai"				, IC_AI				}, // 
	{ "aif"				, IC_AUDIO			}, // 
	{ "aifc"			, IC_AUDIO			}, // 
	{ "aiff"			, IC_AUDIO			}, // 
	{ "alac"			, IC_AUDIO			}, // 
	{ "android"			, IC_OS_ANDROID		}, // 
	{ "ape"				, IC_AUDIO			}, // 
	{ "apk"				, IC_OS_ANDROID		}, // 
	{ "app"				, IC_BINARY			}, // 
	{ "apple"			, IC_OS_APPLE		}, // 
	{ "applescript"		, IC_OS_APPLE		}, // 
	{ "ar"				, IC_COMPRESSED		}, // 
	{ "arj"				, IC_COMPRESSED		}, // 
	{ "arw"				, IC_IMAGE			}, // 
	{ "asc"				, IC_SHIELD_LOCK	}, // 󰦝
	{ "asm"				, IC_LANG_ASSEMBLY	}, // 
	{ "asp"				, IC_ASP			}, // 
	{ "ass"				, IC_SUBTITLE		}, // 󰨖
	{ "avi"				, IC_VIDEOS			}, // 
	{ "avif"			, IC_IMAGE			}, // 
	{ "avro"			, IC_JSON			}, // 
	{ "awk"				, IC_SHELL_CMD		}, // 
	{ "bak"				, IC_BACKUP_FILE	}, // 󰁯  – JV
	{ "bash"			, IC_SHELL_CMD		}, // 
	{ "bat"				, IC_OS_WINDOWS_CMD	}, // 
	{ "bats"			, IC_SHELL_CMD		}, // 
	{ "bdf"				, IC_FONT			}, // 
	{ "bib"				, IC_LANG_TEX		}, // 
	{ "bin"				, IC_BINARY			}, // 
	{ "blend"			, IC_BLEND			}, // 󰂫
	{ "bmp"				, IC_IMAGE			}, // 
	{ "br"				, IC_COMPRESSED		}, // 
	{ "brd"				, IC_EDA_PCB		}, // 
	{ "brep"			, IC_CAD			}, // 󰻫
	{ "bst"				, IC_LANG_TEX		}, // 
	{ "bundle"			, IC_OS_APPLE		}, // 
	{ "bz"				, IC_COMPRESSED		}, // 
	{ "bz2"				, IC_COMPRESSED		}, // 
	{ "bz3"				, IC_COMPRESSED		}, // 
	{ "c"				, IC_LANG_C			}, // 
	{ "c++"				, IC_LANG_CPP		}, // 
	{ "cab"				, IC_OS_WINDOWS		}, // 
	{ "cache"			, IC_CACHE			}, // 
	{ "cast"			, IC_VIDEOS			}, // 
	{ "catpart"			, IC_CAD			}, // 󰻫
	{ "catproduct"		, IC_CAD			}, // 󰻫
	{ "cbr"				, IC_IMAGE			}, // 
	{ "cbz"				, IC_IMAGE			}, // 
	{ "cc"				, IC_LANG_CPP		}, // 
	{ "cert"			, IC_GIST_SECRET	}, // 
	{ "cfg"				, IC_CONFIG			}, // 󱁻
	{ "cjs"				, IC_LANG_JSCPT		}, // 
	{ "class"			, IC_LANG_JAVA		}, // 
	{ "clj"				, IC_CLOJURE_1		}, // 
	{ "cljc"			, IC_CLOJURE_1		}, // 
	{ "cljs"			, IC_CLOJURE_2		}, // 
	{ "cls"				, IC_LANG_TEX		}, // 
	{ "cmake"			, IC_CMAKE			}, // 
	{ "cmd"				, IC_OS_WINDOWS		}, // 
	{ "coffee"			, IC_COFFEE			}, // 
	{ "com"				, IC_COM			}, // 
	{ "conda"			, IC_CONDA			}, // 
	{ "conf"			, IC_CONFIG			}, // 󱁻
	{ "config"			, IC_CONFIG			}, // 󱁻
	{ "cow"				, IC_COW			}, // 󰆚
	{ "cp"				, IC_LANG_CPP		}, // 
	{ "cpio"			, IC_COMPRESSED		}, // 
	{ "cpp"				, IC_LANG_CPP		}, // 
	{ "cr"				, IC_CR				}, // 
	{ "cr2"				, IC_IMAGE			}, // 
	{ "crdownload"		, IC_DOWNLOAD		}, // 󰇚
	{ "crt"				, IC_GIST_SECRET	}, // 
	{ "cs"				, IC_LANG_CSHARP	}, // 󰌛
	{ "csh"				, IC_SHELL_CMD		}, // 
	{ "cshtml"			, IC_RAZOR			}, // 
	{ "csproj"			, IC_LANG_CSHARP	}, // 󰌛
	{ "css"				, IC_CSS3			}, // 
	{ "csv"				, IC_CSV			}, // 
	{ "csx"				, IC_LANG_CSHARP	}, // 󰌛
	{ "cts"				, IC_LANG_TSCPT		}, // 
	{ "cu"				, IC_CU				}, // 
	{ "cue"				, IC_PLAYLIST		}, // 󰲹
	{ "cxx"				, IC_LANG_CPP		}, // 
	{ "d"				, IC_LANG_D			}, // 
	{ "dart"			, IC_DART			}, // 
	{ "db"				, IC_DATABASE		}, // 
	{ "db3"				, IC_SQLITE			}, // 
	{ "dconf"			, IC_DATABASE		}, // 
	{ "deb"				, IC_DEB			}, // 
	{ "desktop"			, IC_DESKTOP_EXT	}, // 
	{ "di"				, IC_LANG_D			}, // 
	{ "diff"			, IC_DIFF			}, // 
	{ "djv"				, IC_DOCUMENT		}, // 
	{ "djvu"			, IC_DOCUMENT		}, // 
	{ "dll"				, IC_LIBRARY		}, // 
	{ "dmg"				, IC_DISK_IMAGE		}, // 
	{ "doc"				, IC_DOCUMENT		}, // 
	{ "dockerfile"		, IC_DOCKER			}, // 
	{ "dockerignore"	, IC_DOCKER			}, // 
	{ "docm"			, IC_DOCUMENT		}, // 
	{ "docx"			, IC_DOCUMENT		}, // 
	{ "dot"				, IC_GRAPH			}, // 󱁉
	{ "download"		, IC_DOWNLOAD		}, // 󰇚
	{ "drawio"			, IC_DRAWIO			}, // 
	{ "dump"			, IC_DATABASE		}, // 
	{ "dvi"				, IC_IMAGE			}, // 
	{ "dwg"				, IC_CAD			}, // 󰻫
	{ "dxf"				, IC_CAD			}, // 󰻫
	{ "dylib"			, IC_OS_APPLE		}, // 
	{ "ebook"			, IC_BOOK			}, // 
	{ "ebuild"			, IC_EBUILD			}, // 
	{ "editorconfig"	, IC_EDITORCONFIG	}, // 
	{ "edn"				, IC_CLOJURE_2		}, // 
	{ "eex"				, IC_LANG_ELIXIR	}, // 
	{ "ejs"				, IC_EJS			}, // 
	{ "el"				, IC_EMACS			}, // 
	{ "elc"				, IC_EMACS			}, // 
	{ "elf"				, IC_BINARY			}, // 
	{ "elm"				, IC_ELM			}, // 
	{ "eml"				, IC_EML			}, // 
	{ "env"				, IC_ENV			}, // 
	{ "eot"				, IC_FONT			}, // 
	{ "eps"				, IC_VECTOR			}, // 󰕙
	{ "epub"			, IC_BOOK			}, // 
	{ "erb"				, IC_LANG_RBRAILS	}, // 
	{ "erl"				, IC_ERLANG			}, // 
	{ "ex"				, IC_LANG_ELIXIR	}, // 
	{ "exe"				, IC_OS_WINDOWS_CMD	}, // 
	{ "exs"				, IC_LANG_ELIXIR	}, // 
	{ "f"				, IC_LANG_FORTRAN	}, // 󱈚
	{ "f#"				, IC_LANG_FSHARP	}, // 
	{ "f3d"				, IC_CAD			}, // 󰻫
	{ "f3z"				, IC_CAD			}, // 󰻫
	{ "f90"				, IC_LANG_FORTRAN	}, // 󱈚
	{ "fbx"				, IC_FILE_3D		}, // 󰆧
	{ "fcbak"			, IC_FREECAD		}, // 
	{ "fcmacro"			, IC_FREECAD		}, // 
	{ "fcmat"			, IC_FREECAD		}, // 
	{ "fcparam"			, IC_FREECAD		}, // 
	{ "fcscript"		, IC_FREECAD		}, // 
	{ "fcstd"			, IC_FREECAD		}, // 
	{ "fcstd1"			, IC_FREECAD		}, // 
	{ "fctb"			, IC_FREECAD		}, // 
	{ "fctl"			, IC_FREECAD		}, // 
	{ "fdmdownload"		, IC_DOWNLOAD		}, // 󰇚
	{ "fish"			, IC_SHELL_CMD		}, // 
	{ "flac"			, IC_AUDIO			}, // 
	{ "flc"				, IC_FONT			}, // 
	{ "flf"				, IC_FONT			}, // 
	{ "flv"				, IC_VIDEOS			}, // 
	{ "fnl"				, IC_LANG_FENNEL	}, // 
	{ "fnt"				, IC_FONT			}, // 
	{ "fodg"			, IC_ODG			}, // 
	{ "fodp"			, IC_ODP			}, // 
	{ "fods"			, IC_ODS			}, // 
	{ "fodt"			, IC_ODT			}, // 
	{ "fon"				, IC_FONT			}, // 
	{ "font"			, IC_FONT			}, // 
	{ "for"				, IC_LANG_FORTRAN	}, // 󱈚
	{ "fs"				, IC_LANG_FSHARP	}, // 
	{ "fsi"				, IC_LANG_FSHARP	}, // 
	{ "fsproj"			, IC_LANG_FSHARP	}, // 
	{ "fsscript"		, IC_LANG_FSHARP	}, // 
	{ "fsx"				, IC_LANG_FSHARP	}, // 
	{ "gba"				, IC_GBA			}, // 󱎓
	{ "gbl"				, IC_EDA_PCB		}, // 
	{ "gbo"				, IC_EDA_PCB		}, // 
	{ "gbp"				, IC_EDA_PCB		}, // 
	{ "gbr"				, IC_EDA_PCB		}, // 
	{ "gbs"				, IC_EDA_PCB		}, // 
	{ "gcode"			, IC_GCODE			}, // 󰫴
	{ "gd"				, IC_GODOT			}, // 
	{ "gdoc"			, IC_DOCUMENT		}, // 
	{ "gem"				, IC_LANG_RUBY		}, // 
	{ "gemfile"			, IC_LANG_RUBY		}, // 
	{ "gemspec"			, IC_LANG_RUBY		}, // 
	{ "gform"			, IC_GFORM			}, // 
	{ "gif"				, IC_IMAGE			}, // 
	{ "git"				, IC_GIT			}, // 󰊢
	{ "gleam"			, IC_LANG_GLEAM		}, // 󰦥
	{ "gm1"				, IC_EDA_PCB		}, // 
	{ "gml"				, IC_EDA_PCB		}, // 
	{ "go"				, IC_LANG_GO		}, // 
	{ "godot"			, IC_GODOT			}, // 
	{ "gpg"				, IC_SHIELD_LOCK	}, // 󰦝
	{ "gql"				, IC_GRAPHQL		}, // 
	{ "gradle"			, IC_GRADLE			}, // 
	{ "graphql"			, IC_GRAPHQL		}, // 
	{ "gresource"		, IC_GTK			}, // 
	{ "groovy"			, IC_LANG_GROOVY	}, // 
	{ "gsheet"			, IC_SHEET			}, // 
	{ "gslides"			, IC_SLIDE			}, // 
	{ "gtl"				, IC_EDA_PCB		}, // 
	{ "gto"				, IC_EDA_PCB		}, // 
	{ "gtp"				, IC_EDA_PCB		}, // 
	{ "gts"				, IC_EDA_PCB		}, // 
	{ "guardfile"		, IC_LANG_RUBY		}, // 
	{ "gv"				, IC_GRAPH			}, // 󱁉
	{ "gvy"				, IC_LANG_GROOVY	}, // 
	{ "gz"				, IC_COMPRESSED		}, // 
	{ "h"				, IC_LANG_C_HEADER	}, //   – JV
	{ "h++"				, IC_LANG_CPP		}, // 
	{ "h264"			, IC_VIDEOS			}, // 
	{ "haml"			, IC_HAML			}, // 
	{ "hbs"				, IC_MUSTACHE		}, // 
	{ "hc"				, IC_LANG_HOLYC		}, // 󰂢
	{ "heic"			, IC_IMAGE			}, // 
	{ "heics"			, IC_VIDEOS			}, // 
	{ "heif"			, IC_IMAGE			}, // 
	{ "hex"				, IC_HEX			}, // 󱊧
	{ "hh"				, IC_LANG_CPP		}, // 
	{ "hi"				, IC_BINARY			}, // 
	{ "hpp"				, IC_LANG_CPP		}, // 
	{ "hrl"				, IC_ERLANG			}, // 
	{ "hs"				, IC_LANG_HASKELL	}, // 
	{ "htm"				, IC_HTML5			}, // 
	{ "html"			, IC_HTML5			}, // 
	{ "hxx"				, IC_LANG_CPP		}, // 
	{ "iam"				, IC_CAD			}, // 󰻫
	{ "ical"			, IC_CALENDAR		}, // 
	{ "icalendar"		, IC_CALENDAR		}, // 
	{ "ico"				, IC_IMAGE			}, // 
	{ "ics"				, IC_CALENDAR		}, // 
	{ "ifb"				, IC_CALENDAR		}, // 
	{ "ifc"				, IC_CAD			}, // 󰻫
	{ "ige"				, IC_CAD			}, // 󰻫
	{ "iges"			, IC_CAD			}, // 󰻫
	{ "igs"				, IC_CAD			}, // 󰻫
	{ "image"			, IC_DISK_IMAGE		}, // 
	{ "img"				, IC_DISK_IMAGE		}, // 
	{ "iml"				, IC_INTELLIJ		}, // 
	{ "info"			, IC_INFO			}, // 
	{ "ini"				, IC_CONFIG			}, // 󱁻
	{ "inl"				, IC_LANG_C			}, // 
	{ "ino"				, IC_LANG_ARDUINO	}, // 
	{ "ipt"				, IC_CAD			}, // 󰻫
	{ "ipynb"			, IC_NOTEBOOK		}, // 
	{ "iso"				, IC_DISK_IMAGE		}, // 
	{ "j2c"				, IC_IMAGE			}, // 
	{ "j2k"				, IC_IMAGE			}, // 
	{ "jad"				, IC_LANG_JAVA		}, // 
	{ "jar"				, IC_LANG_JAVA		}, // 
	{ "java"			, IC_LANG_JAVA		}, // 
	{ "jfi"				, IC_IMAGE			}, // 
	{ "jfif"			, IC_IMAGE			}, // 
	{ "jif"				, IC_IMAGE			}, // 
	{ "jl"				, IC_JL				}, // 
	{ "jmd"				, IC_MARKDOWN		}, // 
	{ "jp2"				, IC_IMAGE			}, // 
	{ "jpe"				, IC_IMAGE			}, // 
	{ "jpeg"			, IC_IMAGE			}, // 
	{ "jpf"				, IC_IMAGE			}, // 
	{ "jpg"				, IC_IMAGE			}, // 
	{ "jpx"				, IC_IMAGE			}, // 
	{ "js"				, IC_LANG_JSCPT		}, // 
	{ "json"			, IC_JSON			}, // 
	{ "json5"			, IC_JSON			}, // 
	{ "jsonc"			, IC_JSON			}, // 
	{ "jsx"				, IC_REACT			}, // 
	{ "jwmrc"			, IC_JWMRC			}, // 
	{ "jxl"				, IC_IMAGE			}, // 
	{ "kbx"				, IC_SHIELD_KEY		}, // 󰯄
	{ "kdb"				, IC_KEYPASS		}, // 
	{ "kdbx"			, IC_KEYPASS		}, // 
	{ "kdenlive"		, IC_KDENLIVE		}, // 
	{ "kdenlivetitle"	, IC_KDENLIVE		}, // 
	{ "key"				, IC_KEY			}, // 
	{ "kicad_dru"		, IC_KICAD			}, // 
	{ "kicad_mod"		, IC_KICAD			}, // 
	{ "kicad_pcb"		, IC_KICAD			}, // 
	{ "kicad_prl"		, IC_KICAD			}, // 
	{ "kicad_pro"		, IC_KICAD			}, // 
	{ "kicad_sch"		, IC_KICAD			}, // 
	{ "kicad_sym"		, IC_KICAD			}, // 
	{ "kicad_wks"		, IC_KICAD			}, // 
	{ "ko"				, IC_OS_LINUX		}, // 
	{ "kpp"				, IC_KRITA			}, // 
	{ "kra"				, IC_KRITA			}, // 
	{ "krz"				, IC_KRITA			}, // 
	{ "ksh"				, IC_SHELL_CMD		}, // 
	{ "kt"				, IC_LANG_KOTLIN	}, // 
	{ "kts"				, IC_LANG_KOTLIN	}, // 
	{ "latex"			, IC_LANG_TEX		}, // 
	{ "lbr"				, IC_LIBRARY		}, // 
	{ "lck"				, IC_LOCK			}, // 
	{ "ldb"				, IC_DATABASE		}, // 
	{ "leex"			, IC_LANG_ELIXIR	}, // 
	{ "less"			, IC_LESS			}, // 
	{ "lff"				, IC_FONT			}, // 
	{ "lhs"				, IC_LANG_HASKELL	}, // 
	{ "lib"				, IC_LIBRARY		}, // 
	{ "license"			, IC_LICENSE		}, // 
	{ "lisp"			, IC_LISP			}, // 󰅲
	{ "localized"		, IC_OS_APPLE		}, // 
	{ "lock"			, IC_LOCK			}, // 
	{ "log"				, IC_LOG			}, // 
	{ "lpp"				, IC_EDA_PCB		}, // 
	{ "lrc"				, IC_SUBTITLE		}, // 󰨖
	{ "ltx"				, IC_LANG_TEX		}, // 
	{ "lua"				, IC_LANG_LUA		}, // 
	{ "luac"			, IC_LANG_LUA		}, // 
	{ "luau"			, IC_LANG_LUA		}, // 
	{ "lz"				, IC_COMPRESSED		}, // 
	{ "lz4"				, IC_COMPRESSED		}, // 
	{ "lzh"				, IC_COMPRESSED		}, // 
	{ "lzma"			, IC_COMPRESSED		}, // 
	{ "lzo"				, IC_COMPRESSED		}, // 
	{ "m"				, IC_LANG_C			}, // 
	{ "m2ts"			, IC_VIDEOS			}, // 
	{ "m2v"				, IC_VIDEOS			}, // 
	{ "m3u"				, IC_PLAYLIST		}, // 󰲹
	{ "m3u8"			, IC_PLAYLIST		}, // 󰲹
	{ "m4a"				, IC_AUDIO			}, // 
	{ "m4v"				, IC_VIDEOS			}, // 
	{ "magnet"			, IC_MAGNET			}, // 
	{ "markdown"		, IC_MARKDOWN		}, // 
	{ "md"				, IC_MARKDOWN		}, // 
	{ "md5"				, IC_SHIELD_CHECK	}, // 󰕥
	{ "mdb"				, IC_DATABASE		}, // 
	{ "mdx"				, IC_MARKDOWN		}, // 
	{ "mid"				, IC_MID			}, // 󰣲
	{ "mjs"				, IC_LANG_JSCPT		}, // 
	{ "mk"				, IC_MAKE			}, // 
	{ "mka"				, IC_AUDIO			}, // 
	{ "mkd"				, IC_MARKDOWN		}, // 
	{ "mkv"				, IC_VIDEOS			}, // 
	{ "ml"				, IC_LANG_OCAML		}, // 
	{ "mli"				, IC_LANG_OCAML		}, // 
	{ "mll"				, IC_LANG_OCAML		}, // 
	{ "mly"				, IC_LANG_OCAML		}, // 
	{ "mm"				, IC_LANG_CPP		}, // 
	{ "mo"				, IC_TRANSLATION	}, // 󰗊
	{ "mobi"			, IC_BOOK			}, // 
	{ "mov"				, IC_VIDEOS			}, // 
	{ "mp2"				, IC_AUDIO			}, // 
	{ "mp3"				, IC_AUDIO			}, // 
	{ "mp4"				, IC_VIDEOS			}, // 
	{ "mpeg"			, IC_VIDEOS			}, // 
	{ "mpg"				, IC_VIDEOS			}, // 
	{ "msf"				, IC_MSF			}, // 
	{ "msi"				, IC_OS_WINDOWS		}, // 
	{ "mts"				, IC_LANG_TSCPT		}, // 
	{ "mustache"		, IC_MUSTACHE		}, // 
	{ "nef"				, IC_IMAGE			}, // 
	{ "nfo"				, IC_INFO			}, // 
	{ "nim"				, IC_LANG_NIM		}, // 
	{ "nimble"			, IC_LANG_NIM		}, // 
	{ "nims"			, IC_LANG_NIM		}, // 
	{ "ninja"			, IC_NINJA			}, // 󰝴
	{ "nix"				, IC_FLAKE			}, // 
	{ "node"			, IC_NODEJS			}, // 
	{ "norg"			, IC_NORG			}, // 
	{ "nsp"				, IC_SWITCH			}, // 󰟡
	{ "nu"				, IC_SHELL_CMD		}, // 
	{ "o"				, IC_BINARY			}, // 
	{ "obj"				, IC_FILE_3D		}, // 󰆧
	{ "odb"				, IC_DATABASE		}, // 
	{ "odf"				, IC_ODF			}, // 
	{ "odg"				, IC_ODG			}, // 
	{ "odp"				, IC_ODP			}, // 
	{ "ods"				, IC_ODS			}, // 
	{ "odt"				, IC_ODT			}, // 
	{ "ogg"				, IC_AUDIO			}, // 
	{ "ogm"				, IC_VIDEOS			}, // 
	{ "ogv"				, IC_VIDEOS			}, // 
	{ "opam"			, IC_OPAM			}, // 󰘧
	{ "opml"			, IC_XML			}, // 󰗀
	{ "opus"			, IC_AUDIO			}, // 
	{ "orf"				, IC_IMAGE			}, // 
	{ "org"				, IC_ORG			}, // 
	{ "otf"				, IC_FONT			}, // 
	{ "out"				, IC_OUT			}, // 
	{ "p12"				, IC_KEY			}, // 
	{ "par"				, IC_COMPRESSED		}, // 
	{ "part"			, IC_DOWNLOAD		}, // 󰇚
	{ "patch"			, IC_DIFF			}, // 
	{ "pbm"				, IC_IMAGE			}, // 
	{ "pcbdoc"			, IC_EDA_PCB		}, // 
	{ "pcm"				, IC_AUDIO			}, // 
	{ "pdf"				, IC_PDF			}, // 
	{ "pem"				, IC_KEY			}, // 
	{ "pfx"				, IC_KEY			}, // 
	{ "pgm"				, IC_IMAGE			}, // 
	{ "phar"			, IC_LANG_PHP		}, // 
	{ "php"				, IC_LANG_PHP		}, // 
	{ "pkg"				, IC_PKG			}, // 
	{ "pl"				, IC_LANG_PERL		}, // 
	{ "plist"			, IC_OS_APPLE		}, // 
	{ "pls"				, IC_PLAYLIST		}, // 󰲹
	{ "plx"				, IC_LANG_PERL		}, // 
	{ "ply"				, IC_FILE_3D		}, // 󰆧
	{ "pm"				, IC_LANG_PERL		}, // 
	{ "png"				, IC_IMAGE			}, // 
	{ "pnm"				, IC_IMAGE			}, // 
	{ "po"				, IC_TRANSLATION	}, // 󰗊
	{ "pod"				, IC_LANG_PERL		}, // 
	{ "pot"				, IC_TRANSLATION	}, // 󰗊
	{ "pp"				, IC_PP				}, // 
	{ "ppm"				, IC_IMAGE			}, // 
	{ "pps"				, IC_SLIDE			}, // 
	{ "ppsx"			, IC_SLIDE			}, // 
	{ "ppt"				, IC_SLIDE			}, // 
	{ "pptx"			, IC_SLIDE			}, // 
	{ "prjpcb"			, IC_EDA_PCB		}, // 
	{ "procfile"		, IC_LANG_RUBY		}, // 
	{ "properties"		, IC_JSON			}, // 
	{ "prql"			, IC_DATABASE		}, // 
	{ "ps"				, IC_VECTOR			}, // 󰕙
	{ "ps1"				, IC_POWERSHELL		}, // 
	{ "psb"				, IC_PHOTOSHOP		}, // 
	{ "psd"				, IC_PHOTOSHOP		}, // 
	{ "psd1"			, IC_POWERSHELL		}, // 
	{ "psf"				, IC_FONT			}, // 
	{ "psm"				, IC_CAD			}, // 󰻫
	{ "psm1"			, IC_POWERSHELL		}, // 
	{ "pub"				, IC_PUBLIC_KEY		}, // 󰷖
	{ "purs"			, IC_PURS			}, // 
	{ "pxd"				, IC_LANG_PYTHON	}, // 
	{ "pxm"				, IC_IMAGE			}, // 
	{ "py"				, IC_LANG_PYTHON	}, // 
	{ "pyc"				, IC_LANG_PYTHON	}, // 
	{ "pyd"				, IC_LANG_PYTHON	}, // 
	{ "pyi"				, IC_LANG_PYTHON	}, // 
	{ "pyo"				, IC_LANG_PYTHON	}, // 
	{ "pyw"				, IC_LANG_PYTHON	}, // 
	{ "pyx"				, IC_LANG_PYTHON	}, // 
	{ "qcow"			, IC_DISK_IMAGE		}, // 
	{ "qcow2"			, IC_DISK_IMAGE		}, // 
	{ "qm"				, IC_TRANSLATION	}, // 󰗊
	{ "qml"				, IC_QT				}, // 
	{ "qrc"				, IC_QT				}, // 
	{ "qss"				, IC_QT				}, // 
	{ "r"				, IC_LANG_R			}, // 
	{ "rake"			, IC_LANG_RUBY		}, // 
	{ "rakefile"		, IC_LANG_RUBY		}, // 
	{ "rar"				, IC_COMPRESSED		}, // 
	{ "raw"				, IC_IMAGE			}, // 
	{ "razor"			, IC_RAZOR			}, // 
	{ "rb"				, IC_LANG_RUBY		}, // 
	{ "rdata"			, IC_LANG_R			}, // 
	{ "rdb"				, IC_RDB			}, // 
	{ "rdoc"			, IC_MARKDOWN		}, // 
	{ "rds"				, IC_LANG_R			}, // 
	{ "readme"			, IC_README			}, // 󰂺
	{ "rkt"				, IC_LANG_SCHEME	}, // 
	{ "rlib"			, IC_LANG_RUST		}, // 
	{ "rmd"				, IC_MARKDOWN		}, // 
	{ "rmeta"			, IC_LANG_RUST		}, // 
	{ "rpm"				, IC_RPM			}, // 
	{ "rs"				, IC_LANG_RUST		}, // 
	{ "rspec_parallel"	, IC_LANG_RUBY		}, // 
	{ "rspec_status"	, IC_LANG_RUBY		}, // 
	{ "rspec"			, IC_LANG_RUBY		}, // 
	{ "rss"				, IC_RSS			}, // 
	{ "rst"				, IC_TEXT			}, // 
	{ "rtf"				, IC_TEXT			}, // 
	{ "ru"				, IC_LANG_RUBY		}, // 
	{ "rubydoc"			, IC_LANG_RBRAILS	}, // 
	{ "s"				, IC_LANG_ASSEMBLY	}, // 
	{ "s3db"			, IC_SQLITE			}, // 
	{ "sal"				, IC_SQ_WAVE		}, // 󱑻
	{ "sass"			, IC_LANG_SASS		}, // 
	{ "sbt"				, IC_SUBTITLE		}, // 󰨖
	{ "scad"			, IC_SCAD			}, // 
	{ "scala"			, IC_SCALA			}, // 
	{ "sch"				, IC_EDA_SCH		}, // 󰭅
	{ "schdoc"			, IC_EDA_SCH		}, // 󰭅
	{ "scm"				, IC_LANG_SCHEME	}, // 
	{ "scss"			, IC_LANG_SASS		}, // 
	{ "service"			, IC_SERVICE		}, // 
	{ "sf2"				, IC_TREB_CLEF		}, // 󰽰
	{ "sfz"				, IC_TREB_CLEF		}, // 󰽰
	{ "sh"				, IC_SHELL_CMD		}, // 
	{ "sha1"			, IC_SHIELD_CHECK	}, // 󰕥
	{ "sha224"			, IC_SHIELD_CHECK	}, // 󰕥
	{ "sha256"			, IC_SHIELD_CHECK	}, // 󰕥
	{ "sha384"			, IC_SHIELD_CHECK	}, // 󰕥
	{ "sha512"			, IC_SHIELD_CHECK	}, // 󰕥
	{ "shell"			, IC_SHELL_CMD		}, // 
	{ "shtml"			, IC_HTML5			}, // 
	{ "sig"				, IC_SIGNED_FILE	}, // 󱧃
	{ "signature"		, IC_SIGNED_FILE	}, // 󱧃
	{ "skp"				, IC_CAD			}, // 󰻫
	{ "sl3"				, IC_SQLITE			}, // 
	{ "sld"				, IC_LANG_SCHEME	}, // 
	{ "sldasm"			, IC_CAD			}, // 󰻫
	{ "sldprt"			, IC_CAD			}, // 󰻫
	{ "slim"			, IC_LANG_RBRAILS	}, // 
	{ "sln"				, IC_VSCODE			}, // 
	{ "slvs"			, IC_CAD			}, // 󰻫
	{ "so"				, IC_OS_LINUX		}, // 
	{ "sql"				, IC_DATABASE		}, // 
	{ "sqlite"			, IC_SQLITE			}, // 
	{ "sqlite3"			, IC_SQLITE			}, // 
	{ "sr"				, IC_SQ_WAVE		}, // 󱑻
	{ "srt"				, IC_SUBTITLE		}, // 󰨖
	{ "ss"				, IC_LANG_SCHEME	}, // 
	{ "ssa"				, IC_SUBTITLE		}, // 󰨖
	{ "ste"				, IC_CAD			}, // 󰻫
	{ "step"			, IC_CAD			}, // 󰻫
	{ "stl"				, IC_FILE_3D		}, // 󰆧
	{ "stp"				, IC_CAD			}, // 󰻫
	{ "sty"				, IC_LANG_TEX		}, // 
	{ "styl"			, IC_LANG_STYLUS	}, // 
	{ "stylus"			, IC_LANG_STYLUS	}, // 
	{ "sub"				, IC_SUBTITLE		}, // 󰨖
	{ "sublime-build"	, IC_SUBLIME		}, // 
	{ "sublime-keymap"	, IC_SUBLIME		}, // 
	{ "sublime-menu"	, IC_SUBLIME		}, // 
	{ "sublime-options"	, IC_SUBLIME		}, // 
	{ "sublime-package"	, IC_SUBLIME		}, // 
	{ "sublime-project"	, IC_SUBLIME		}, // 
	{ "sublime-session"	, IC_SUBLIME		}, // 
	{ "sublime-settings", IC_SUBLIME		}, // 
	{ "sublime-snippet"	, IC_SUBLIME		}, // 
	{ "sublime-theme"	, IC_SUBLIME		}, // 
	{ "suo"				, IC_VSCODE			}, // 
	{ "sv"				, IC_LANG_HDL		}, // 󰍛
	{ "svelte"			, IC_SVELTE			}, // 
	{ "svg"				, IC_VECTOR			}, // 󰕙
	{ "svh"				, IC_LANG_HDL		}, // 󰍛
	{ "swf"				, IC_AUDIO			}, // 
	{ "swift"			, IC_SWIFT			}, // 
	{ "t"				, IC_LANG_PERL		}, // 
	{ "tar"				, IC_COMPRESSED		}, // 
	{ "taz"				, IC_COMPRESSED		}, // 
	{ "tbc"				, IC_TCL			}, // 󰛓
	{ "tbz"				, IC_COMPRESSED		}, // 
	{ "tbz2"			, IC_COMPRESSED		}, // 
	{ "tc"				, IC_DISK_IMAGE		}, // 
	{ "tcl"				, IC_TCL			}, // 󰛓
	{ "tex"				, IC_LANG_TEX		}, // 
	{ "tf"				, IC_TERRAFORM		}, // 󱁢
	{ "tfstate"			, IC_TERRAFORM		}, // 󱁢
	{ "tfvars"			, IC_TERRAFORM		}, // 󱁢
	{ "tgz"				, IC_COMPRESSED		}, // 
	{ "tif"				, IC_IMAGE			}, // 
	{ "tiff"			, IC_IMAGE			}, // 
	{ "tlz"				, IC_COMPRESSED		}, // 
	{ "tml"				, IC_CONFIG			}, // 󱁻
	{ "tmux"			, IC_TMUX			}, // 
	{ "toml"			, IC_TOML			}, // 
	{ "torrent"			, IC_TORRENT		}, // 
	{ "tres"			, IC_GODOT			}, // 
	{ "ts"				, IC_LANG_TSCPT		}, // 
	{ "tscn"			, IC_GODOT			}, // 
	{ "tsv"				, IC_SHEET			}, // 
	{ "tsx"				, IC_REACT			}, // 
	{ "ttc"				, IC_FONT			}, // 
	{ "ttf"				, IC_FONT			}, // 
	{ "twig"			, IC_TWIG			}, // 
	{ "txt"				, IC_TEXT			}, // 
	{ "txz"				, IC_COMPRESSED		}, // 
	{ "typ"				, IC_TYPST			}, // 
	{ "tz"				, IC_COMPRESSED		}, // 
	{ "tzo"				, IC_COMPRESSED		}, // 
	{ "ui"				, IC_UI				}, // 
	{ "unity"			, IC_UNITY			}, // 
	{ "unity3d"			, IC_UNITY			}, // 
	{ "v"				, IC_LANG_V			}, // 
	{ "vala"			, IC_VALA			}, // 
	{ "vdi"				, IC_DISK_IMAGE		}, // 
	{ "vhd"				, IC_DISK_IMAGE		}, // 
	{ "vhdl"			, IC_LANG_HDL		}, // 󰍛
	{ "vhs"				, IC_VHS			}, // 󰨛
	{ "vi"				, IC_VI				}, // 
	{ "video"			, IC_VIDEOS			}, // 
	{ "vim"				, IC_VIM			}, // 
	{ "vmdk"			, IC_DISK_IMAGE		}, // 
	{ "vob"				, IC_VIDEOS			}, // 
	{ "vsix"			, IC_VSIX			}, // 󰨞
	{ "vue"				, IC_VUE			}, // 󰡄
	{ "war"				, IC_LANG_JAVA		}, // 
	{ "wav"				, IC_AUDIO			}, // 
	{ "webm"			, IC_VIDEOS			}, // 
	{ "webmanifest"		, IC_JSON			}, // 
	{ "webp"			, IC_IMAGE			}, // 
	{ "whl"				, IC_LANG_PYTHON	}, // 
	{ "windows"			, IC_OS_WINDOWS		}, // 
	{ "wma"				, IC_AUDIO			}, // 
	{ "wmv"				, IC_VIDEOS			}, // 
	{ "woff"			, IC_FONT			}, // 
	{ "woff2"			, IC_FONT			}, // 
	{ "wrl"				, IC_FILE_3D		}, // 󰆧
	{ "wrz"				, IC_FILE_3D		}, // 󰆧
	{ "wv"				, IC_AUDIO			}, // 
	{ "x_b"				, IC_CAD			}, // 󰻫
	{ "x_t"				, IC_CAD			}, // 󰻫
	{ "xaml"			, IC_XAML			}, // 󰙳
	{ "xcf"				, IC_GIMP			}, // 
	{ "xci"				, IC_SWITCH			}, // 󰟡
	{ "xcplayground"	, IC_SWIFT			}, // 
	{ "xhtml"			, IC_HTML5			}, // 
	{ "xlr"				, IC_SHEET			}, // 
	{ "xls"				, IC_SHEET			}, // 
	{ "xlsm"			, IC_SHEET			}, // 
	{ "xlsx"			, IC_SHEET			}, // 
	{ "xml"				, IC_XML			}, // 󰗀
	{ "xpi"				, IC_XPI			}, // 
	{ "xpm"				, IC_IMAGE			}, // 
	{ "xul"				, IC_XML			}, // 󰗀
	{ "xz"				, IC_COMPRESSED		}, // 
	{ "yaml"			, IC_YAML			}, // 
	{ "yml"				, IC_YAML			}, // 
	{ "z"				, IC_COMPRESSED		}, // 
	{ "z64"				, IC_GBA			}, // 󱎓
	{ "zig"				, IC_ZIG			}, // 
	{ "zip"				, IC_COMPRESSED		}, // 
	{ "zsh-theme"		, IC_SHELL			}, // 󱆃
	{ "zsh"				, IC_SHELL_CMD		}, // 
	{ "zst"				, IC_COMPRESSED		}, // 
	END_OF_ICONS
};

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignoreRegexp /((?<=\bIC_)\w+|(?<=\{[ \t]+")[\w-.]+(?=")/g
