#ifndef LOCATION_HPP
#define LOCATION_HPP


struct Location
{
    Location(const char *file, const char *func, int line)
      : file_(file),
        func_(func),
        line_(line)
    {}

    const char *file_ = "";
    const char *func_ = "";
    int line_         = -1;
};

#define LOCATION Location{__FILE__, __FUNCTION__, __LINE__}

#endif
