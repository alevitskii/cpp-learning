// global variable definitions
int g_x{ 2 }; // non-constant globals have external linkage by default
extern const int g_y{ 3 }; // this extern gives g_y external linkage

// constexpr can also have external linkage but they can be forward declared because compliler must know its value
// during compile time. However it's possible to forward declare it as const
extern constexpr int g_z{ 3 }; // this extern gives g_z external linkage
