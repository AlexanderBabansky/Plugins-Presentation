#pragma once

class MyUnknown;
typedef void(*PluginPassHostType)(MyUnknown*);
constexpr char PluginPassHostName[15] = "PluginPassHost";
#define PluginPassHostMethod PluginPassHost
