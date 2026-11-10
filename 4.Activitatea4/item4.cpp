#include "item4.h"

FileSystem& tfs() {
    static FileSystem fs;
    return fs;
}
