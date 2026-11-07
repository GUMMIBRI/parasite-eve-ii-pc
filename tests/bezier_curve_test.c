#include "../src/shared/actor/bezier_curve.h"
#include "../src/shared/actor/bezier_curve_coefficients.inc.c"
#include "../src/shared/actor/bezier_curve_evaluate.inc.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHECK(x) do { if (!(x)) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
int main(void)
{
    struct { u32 before; VECTOR point; u32 after; } output;
    SVECTOR controls[4] = {{-123,456,-789,0},{-123,456,-789,0},{-123,456,-789,0},{-123,456,-789,0}};
    memset(&output, 0xa5, sizeof(output));
    for (int step = 0; step <= 9; ++step) {
        _bezierCurveEvaluate(controls, &controls[3], 9, step, &output.point.vx);
        CHECK(output.point.vx == -123 && output.point.vy == 456 && output.point.vz == -789);
        CHECK(output.before == 0xa5a5a5a5u && output.after == 0xa5a5a5a5u);
        CHECK((u32)output.point.pad == 0xa5a5a5a5u);
    }
    for (int i = 0; i < 4; ++i) { controls[i].vx = i * 100; controls[i].vy = i * 200; controls[i].vz = -i * 100; }
    _bezierCurveEvaluate(controls, &controls[3], 2, 1, &output.point.vx);
    CHECK(output.point.vx == 149 && output.point.vy == 299 && output.point.vz == -150);
    _bezierCurveEvaluate(NULL, NULL, 0, 0, NULL);
    puts("Bezier: fixed-width XYZ writes preserve VECTOR padding and adjacent storage");
    return 0;
}
