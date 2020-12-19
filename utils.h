#ifndef UTILS_H
#define UTILS_H

#define null 0
typedef unsigned int uint;
#define internal static

#define alloc(t) _alloc<t>()
template<typename T> T *_alloc() { 
    T *value = (T *)malloc(sizeof(T));
    
    T dummy; 
    memcpy(value, &dummy, sizeof(T));
    
    return value;
}

#define allocn(t, n) _allocn<t>(n)
template<typename T> T *_allocn(int n) {
    T *values = (T *)malloc(sizeof(T) * n);
    T dummy;
    for(int i = 0; i < n; i++) memcpy(&values[i], &dummy, sizeof(T));
    return values;
}

void log(const char *subject, const char *text, ...) {
    va_list args;
    printf("[%s] - ", subject);
    va_start(args, text);
    vprintf(text, args);
    va_end(args);
}

// Taken (stolen) from Jon Blow.
// Defer macro/thing

#define CONCAT_INTERNAL(x,y) x##y
#define CONCAT(x,y) CONCAT_INTERNAL(x,y)

template<typename T>
struct Exit_Scope {
    T lambda;
    Exit_Scope(T lambda) : lambda(lambda) {}
    ~Exit_Scope() { lambda(); }
    Exit_Scope(const Exit_Scope&);
    private:
    Exit_Scope &operator=(const Exit_Scope&);
};

class Exit_Scope_Help {
    public:
    template<typename T> Exit_Scope<T> operator+(T t){ return t; }
};

#define defer const auto &CONCAT(defer__, __LINE__) = Exit_Scope_Help() + [&]()

#ifdef assert
#undef assert
#endif

#ifdef _WINDOWS
#define assert(x, m, ...) { if (!_assert(x, __FILE__, __LINE__, m, __VA_ARGS__)) if(IsDebuggerPresent()) __debugbreak(); }
#else 
#define assert(x, m, ...) _assert(x, __FILE__, __LINE__, m, __VA_ARGS__)
#endif

inline bool _assert(bool condition, const char *file, int line,  const char *message, ...) {
    va_list args;
    
    if(!condition) {
        printf("*** ASSERTION FAILED ***\n");
        printf("At %s(%d): ", file, line);
        va_start(args, message);
        vprintf(message, args);
        va_end(args);
        printf("\n");
    }
    
    return condition;
}

void quit();
void fatal_error(const char *title, const char *text, ...);

struct Load_File_Result {
	char *data = nullptr;
	int length = 0;
};

Load_File_Result load_entire_file(const char *filename);

extern SDL_Window *sdl_window;
extern float current_time;
extern float delta_time;
extern Vec2 cursor_position;

#endif
