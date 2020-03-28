#pragma once

static uint8_t map256_64[256][4] = {
  {26, 44, 36, 1},
  {54, 44, 39, 1},
  {51, 46, 34, 1},
  {51, 23, 61, 1},
  {21, 7,  24, 2},
  {16, 50, 38, 2},
  {57, 47, 0, 2},
  {36, 19, 31, 2},
  {56, 4,  21, 3},
  {7,  62, 57, 3},
  {33, 38, 44, 3},
  {1,  62, 58, 3},
  {47, 11, 35, 4},
  {63, 11, 29, 4},
  {25, 32, 20, 4},
  {52, 38, 5,  4},
  {9,  3,  27, 5},
  {62, 3,  14, 5},
  {45, 34, 23, 5},
  {25, 58, 22, 5},
  {13, 37, 59, 6},
  {33, 10, 39, 6},
  {46, 2,  26, 6},
  {59, 28, 26, 6},
  {44, 35, 23, 7},
  {29, 1,  35, 7},
  {57, 46, 14, 7},
  {30, 20, 61, 7},
  {28, 9,  1,  8},
  {24, 56, 45, 8},
  {14, 55, 57, 8},
  {52, 14, 10, 8},
  {63, 52, 49, 9},
  {49, 33, 51, 9},
  {12, 40, 61, 9},
  {25, 58, 45, 9},
  {58, 46, 45, 10},
  {45, 1,  42, 10},
  {5,  19, 51, 10},
  {8,  6,  14, 10},
  {44, 39, 51, 11},
  {3,  21, 32, 11},
  {57, 35, 0, 11},
  {35, 15, 12, 11},
  {19, 63, 20, 12},
  {19, 27, 16, 12},
  {44, 62, 41, 12},
  {30, 2,  42, 12},
  {56, 57, 43, 13},
  {26, 24, 49, 13},
  {34, 0, 28, 13},
  {23, 51, 15, 13},
  {60, 62, 25, 14},
  {60, 49, 3,  14},
  {60, 28, 20, 14},
  {47, 9,  24, 14},
  {39, 10, 53, 15},
  {54, 47, 63, 15},
  {22, 36, 39, 15},
  {53, 12, 33, 15},
  {24, 21, 10, 16},
  {10, 56, 32, 16},
  {31, 24, 46, 16},
  {18, 38, 17, 16},
  {16, 48, 3,  17},
  {56, 4,  8,  17},
  {0, 8,  56, 17},
  {27, 11, 53, 17},
  {2,  63, 47, 18},
  {31, 14, 30, 18},
  {36, 56, 3,  18},
  {46, 63, 54, 18},
  {31, 6,  48, 19},
  {18, 10, 54, 19},
  {40, 6,  18, 19},
  {5,  14, 56, 19},
  {19, 14, 42, 20},
  {3,  49, 62, 20},
  {42, 60, 10, 20},
  {31, 27, 41, 20},
  {4,  42, 11, 21},
  {17, 36, 0, 21},
  {49, 29, 19, 21},
  {22, 51, 12, 21},
  {50, 49, 11, 22},
  {15, 6,  59, 22},
  {19, 32, 43, 22},
  {25, 47, 32, 22},
  {32, 0, 30, 23},
  {3,  60, 8,  23},
  {45, 58, 27, 23},
  {11, 51, 7,  23},
  {46, 58, 34, 24},
  {40, 35, 63, 24},
  {13, 16, 52, 24},
  {17, 29, 45, 24},
  {58, 8,  10, 25},
  {29, 53, 32, 25},
  {34, 2,  59, 25},
  {29, 13, 43, 25},
  {52, 3,  29, 26},
  {54, 12, 53, 26},
  {50, 35, 37, 26},
  {45, 23, 36, 26},
  {22, 50, 63, 27},
  {43, 48, 50, 27},
  {38, 60, 50, 27},
  {22, 5,  56, 27},
  {48, 60, 57, 28},
  {30, 4,  7,  28},
  {55, 22, 15, 28},
  {29, 12, 4,  28},
  {3,  54, 6,  29},
  {33, 3,  44, 29},
  {52, 23, 3,  29},
  {32, 15, 12, 29},
  {12, 1,  36, 30},
  {12, 16, 11, 30},
  {16, 25, 12, 30},
  {40, 45, 24, 30},
  {40, 13, 39, 31},
  {36, 18, 33, 31},
  {37, 53, 41, 31},
  {33, 7,  50, 31},
  {14, 18, 52, 32},
  {14, 37, 48, 32},
  {23, 48, 38, 32},
  {48, 22, 16, 32},
  {30, 5,  20, 33},
  {20, 28, 5,  33},
  {32, 50, 59, 33},
  {55, 49, 54, 33},
  {15, 7,  16, 34},
  {27, 12, 57, 34},
  {17, 15, 63, 34},
  {50, 33, 56, 34},
  {14, 18, 33, 35},
  {10, 47, 8,  35},
  {16, 18, 55, 35},
  {46, 36, 26, 35},
  {32, 0, 37, 36},
  {35, 22, 52, 36},
  {38, 9,  15, 36},
  {27, 41, 48, 36},
  {17, 24, 61, 37},
  {61, 28, 53, 37},
  {6,  63, 7,  37},
  {28, 26, 5,  37},
  {41, 53, 18, 38},
  {21, 0, 36, 38},
  {54, 2,  44, 38},
  {62, 33, 47, 38},
  {56, 21, 8,  39},
  {51, 29, 46, 39},
  {58, 13, 23, 39},
  {55, 38, 58, 39},
  {15, 19, 62, 40},
  {4,  5,  46, 40},
  {15, 44, 30, 40},
  {59, 26, 14, 40},
  {8,  52, 27, 41},
  {10, 13, 5,  41},
  {2,  16, 47, 41},
  {58, 4,  60, 41},
  {49, 55, 47, 42},
  {20, 26, 33, 42},
  {18, 51, 16, 42},
  {51, 17, 2,  42},
  {27, 39, 41, 43},
  {1,  45, 19, 43},
  {55, 26, 23, 43},
  {38, 53, 27, 43},
  {21, 42, 6,  44},
  {8,  37, 19, 44},
  {18, 52, 55, 44},
  {63, 32, 17, 44},
  {59, 5,  48, 45},
  {57, 15, 51, 45},
  {8,  61, 62, 45},
  {23, 7,  52, 45},
  {13, 57, 17, 46},
  {44, 10, 49, 46},
  {39, 52, 50, 46},
  {26, 20, 21, 46},
  {48, 33, 42, 47},
  {35, 39, 13, 47},
  {5,  41, 43, 47},
  {4,  1,  28, 47},
  {61, 23, 22, 48},
  {10, 42, 60, 48},
  {41, 39, 58, 48},
  {12, 16, 17, 48},
  {2,  41, 60, 49},
  {24, 50, 19, 49},
  {59, 43, 7,  49},
  {13, 54, 35, 49},
  {23, 30, 34, 50},
  {53, 24, 29, 50},
  {39, 42, 58, 50},
  {1,  32, 13, 50},
  {50, 19, 54, 51},
  {36, 40, 37, 51},
  {42, 31, 21, 51},
  {53, 59, 31, 51},
  {42, 31, 30, 52},
  {49, 43, 55, 52},
  {34, 36, 25, 52},
  {7,  29, 24, 52},
  {34, 22, 40, 53},
  {5,  54, 1,  53},
  {35, 9,  60, 53},
  {63, 55, 37, 53},
  {11, 59, 26, 54},
  {2,  61, 40, 54},
  {41, 44, 11, 54},
  {53, 40, 9,  54},
  {47, 43, 49, 55},
  {39, 57, 38, 55},
  {43, 27, 46, 55},
  {4,  25, 62, 55},
  {41, 61, 2,  56},
  {11, 27, 44, 56},
  {47, 46, 38, 56},
  {7,  55, 29, 56},
  {37, 61, 1,  57},
  {37, 48, 55, 57},
  {0, 11, 31, 57},
  {24, 40, 18, 57},
  {9,  56, 25, 58},
  {61, 30, 9,  58},
  {60, 17, 1,  58},
  {6,  43, 25, 58},
  {62, 25, 40, 59},
  {20, 41, 31, 59},
  {42, 54, 6,  59},
  {26, 17, 4,  59},
  {0, 25, 4,  60},
  {48, 34, 9,  60},
  {20, 21, 9,  60},
  {28, 8,  0, 60},
  {38, 59, 4,  61},
  {9,  17, 34, 61},
  {43, 20, 40, 61},
  {28, 31, 35, 61},
  {37, 20, 2,  62},
  {61, 8,  22, 62},
  {0, 57, 21, 62},
  {6,  34, 15, 62},
  {1,  59, 28, 63},
  {62, 31, 22, 63},
  {43, 45, 6,  63},
  {21, 30, 13, 63},
  {7,  45, 18, 0},
  {6,  34, 13, 0},
  {9,  37, 2,  0},
  {11, 30, 28, 0},
};
