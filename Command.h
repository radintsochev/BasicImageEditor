#pragma once

template <typename T>
class Command{
public:
    virtual void apply(T& image) {}
    virtual void apply(const char* direction, T& image) {}
    virtual void apply(const char* direction, T& firstImage, T& secondImage, const char* outImageName) {}
    virtual ~Command() {}
};