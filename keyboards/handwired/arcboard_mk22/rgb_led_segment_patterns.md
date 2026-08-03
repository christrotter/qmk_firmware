# RGB LED Segment Patterns (arcboard_mk22)

Goal: keep segment math maintainable while still addressing contiguous regions of a single LED chain by index.

This file shows two patterns you can use instead of manually expanding every START/END symbol.

## Pattern 1: Macro-only, computed ranges

Use one set of size constants and derive all starts/ends from a base.

```c
// Segment sizes (single source of truth)
#define RGB_SEG_COUNT_KEYS            37
#define RGB_SEG_COUNT_RING            16
#define RGB_SEG_COUNT_INDICATOR       16
#define RGB_SEG_COUNT_INDICATOR_SPLIT 4
#define RGB_SEG_COUNT_INNER_INTAKE    10
#define RGB_SEG_COUNT_OUTER_INTAKE    12
#define RGB_SEG_COUNT_LOGO            12

// Optional wiring gap between sections
#define RGB_SEG_GAP_RIGHT_RING        4

// Helper macros
#define RGB_SEG_END(start, len)       ((start) + (len) - 1)
#define RGB_SEG_NEXT(start, len)      ((start) + (len))

// Left side
#define RGB_KEYS_L_START              0
#define RGB_KEYS_L_END                RGB_SEG_END(RGB_KEYS_L_START, RGB_SEG_COUNT_KEYS)

#define RGB_RING_L_START              RGB_SEG_NEXT(RGB_KEYS_L_START, RGB_SEG_COUNT_KEYS)
#define RGB_RING_L_END                RGB_SEG_END(RGB_RING_L_START, RGB_SEG_COUNT_RING)

#define RGB_INDICATOR_L_START         RGB_SEG_NEXT(RGB_RING_L_START, RGB_SEG_COUNT_RING)
#define RGB_INDICATOR_L_END           RGB_SEG_END(RGB_INDICATOR_L_START, RGB_SEG_COUNT_INDICATOR)

#define RGB_INDICATOR_L1_START        RGB_INDICATOR_L_START
#define RGB_INDICATOR_L1_END          RGB_SEG_END(RGB_INDICATOR_L1_START, RGB_SEG_COUNT_INDICATOR_SPLIT)
#define RGB_INDICATOR_L2_START        RGB_SEG_NEXT(RGB_INDICATOR_L1_START, RGB_SEG_COUNT_INDICATOR_SPLIT)
#define RGB_INDICATOR_L2_END          RGB_INDICATOR_L_END

#define RGB_INNER_INTAKE_L_START      RGB_SEG_NEXT(RGB_INDICATOR_L_START, RGB_SEG_COUNT_INDICATOR)
#define RGB_INNER_INTAKE_L_END        RGB_SEG_END(RGB_INNER_INTAKE_L_START, RGB_SEG_COUNT_INNER_INTAKE)

#define RGB_OUTER_INTAKE_L_START      RGB_SEG_NEXT(RGB_INNER_INTAKE_L_START, RGB_SEG_COUNT_INNER_INTAKE)
#define RGB_OUTER_INTAKE_L_END        RGB_SEG_END(RGB_OUTER_INTAKE_L_START, RGB_SEG_COUNT_OUTER_INTAKE)

#define RGB_LOGO_L_START              RGB_SEG_NEXT(RGB_OUTER_INTAKE_L_START, RGB_SEG_COUNT_OUTER_INTAKE)
#define RGB_LOGO_L_END                RGB_SEG_END(RGB_LOGO_L_START, RGB_SEG_COUNT_LOGO)

// Right side
#define RGB_KEYS_R_START              RGB_SEG_NEXT(RGB_LOGO_L_START, RGB_SEG_COUNT_LOGO)
#define RGB_KEYS_R_END                RGB_SEG_END(RGB_KEYS_R_START, RGB_SEG_COUNT_KEYS)

#define RGB_RING_R_START              (RGB_SEG_NEXT(RGB_KEYS_R_START, RGB_SEG_COUNT_KEYS) + RGB_SEG_GAP_RIGHT_RING)
#define RGB_RING_R_END                RGB_SEG_END(RGB_RING_R_START, RGB_SEG_COUNT_RING)

#define RGB_INDICATOR_R_START         RGB_SEG_NEXT(RGB_RING_R_START, RGB_SEG_COUNT_RING)
#define RGB_INDICATOR_R_END           RGB_SEG_END(RGB_INDICATOR_R_START, RGB_SEG_COUNT_INDICATOR)

#define RGB_INDICATOR_R1_START        RGB_INDICATOR_R_START
#define RGB_INDICATOR_R1_END          RGB_SEG_END(RGB_INDICATOR_R1_START, RGB_SEG_COUNT_INDICATOR_SPLIT)
#define RGB_INDICATOR_R2_START        RGB_SEG_NEXT(RGB_INDICATOR_R1_START, RGB_SEG_COUNT_INDICATOR_SPLIT)
#define RGB_INDICATOR_R2_END          RGB_INDICATOR_R_END

#define RGB_INNER_INTAKE_R_START      RGB_SEG_NEXT(RGB_INDICATOR_R_START, RGB_SEG_COUNT_INDICATOR)
#define RGB_INNER_INTAKE_R_END        RGB_SEG_END(RGB_INNER_INTAKE_R_START, RGB_SEG_COUNT_INNER_INTAKE)

#define RGB_OUTER_INTAKE_R_START      RGB_SEG_NEXT(RGB_INNER_INTAKE_R_START, RGB_SEG_COUNT_INNER_INTAKE)
#define RGB_OUTER_INTAKE_R_END        RGB_SEG_END(RGB_OUTER_INTAKE_R_START, RGB_SEG_COUNT_OUTER_INTAKE)

#define RGB_LOGO_R_START              RGB_SEG_NEXT(RGB_OUTER_INTAKE_R_START, RGB_SEG_COUNT_OUTER_INTAKE)
#define RGB_LOGO_R_END                RGB_SEG_END(RGB_LOGO_R_START, RGB_SEG_COUNT_LOGO)
```

Why use this:
- No hand-maintained duplicated arithmetic in each END macro.
- Start/end stay deterministic at compile time.
- Easy to change a segment length in one place.

## Pattern 2: Table-driven segments (C struct + enum)

Use a segment table for easier iteration and function-based access.

```c
// Put this in a .c/.h pair used by your rgb code.
typedef enum {
    SEG_KEYS_L,
    SEG_RING_L,
    SEG_INDICATOR_L,
    SEG_INDICATOR_L1,
    SEG_INDICATOR_L2,
    SEG_INNER_INTAKE_L,
    SEG_OUTER_INTAKE_L,
    SEG_LOGO_L,
    SEG_KEYS_R,
    SEG_RING_R,
    SEG_INDICATOR_R,
    SEG_INDICATOR_R1,
    SEG_INDICATOR_R2,
    SEG_INNER_INTAKE_R,
    SEG_OUTER_INTAKE_R,
    SEG_LOGO_R,
    SEG_COUNT
} rgb_segment_id_t;

typedef struct {
    uint16_t start;
    uint16_t len;
} rgb_segment_t;

#define GAP_RIGHT_RING 4

static const rgb_segment_t rgb_segments[SEG_COUNT] = {
    [SEG_KEYS_L]         = {  0, 37 },
    [SEG_RING_L]         = { 37, 16 },
    [SEG_INDICATOR_L]    = { 53, 16 },
    [SEG_INDICATOR_L1]   = { 53,  4 },
    [SEG_INDICATOR_L2]   = { 57, 12 },
    [SEG_INNER_INTAKE_L] = { 69, 10 },
    [SEG_OUTER_INTAKE_L] = { 79, 12 },
    [SEG_LOGO_L]         = { 91, 12 },
    [SEG_KEYS_R]         = {103, 37 },
    [SEG_RING_R]         = {144, 16 }, // includes +4 wiring gap from 140 to 143
    [SEG_INDICATOR_R]    = {160, 16 },
    [SEG_INDICATOR_R1]   = {160,  4 },
    [SEG_INDICATOR_R2]   = {164, 12 },
    [SEG_INNER_INTAKE_R] = {176, 10 },
    [SEG_OUTER_INTAKE_R] = {186, 12 },
    [SEG_LOGO_R]         = {198, 12 }
};

static inline uint16_t seg_start(rgb_segment_id_t id) {
    return rgb_segments[id].start;
}

static inline uint16_t seg_end(rgb_segment_id_t id) {
    return rgb_segments[id].start + rgb_segments[id].len - 1;
}

static inline void set_segment_color(rgb_segment_id_t id, uint8_t r, uint8_t g, uint8_t b) {
    uint16_t start = seg_start(id);
    uint16_t end = seg_end(id);
    for (uint16_t i = start; i <= end; ++i) {
        rgb_matrix_set_color(i, r, g, b);
    }
}
```

Why use this:
- Segment definitions are centralized and readable.
- Easy to loop over segments or build effects by segment ID.
- Great when segments may change by board revision.

## Choosing between them

Pick Pattern 1 if you want zero runtime overhead and config-like compile-time constants.

Pick Pattern 2 if you want cleaner effect code that addresses segments by name/ID and easier future refactors.
