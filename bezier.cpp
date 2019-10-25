

//generateRMFrames(steps) -> frames:
//step = 1.0/steps
//
//// Start off with the standard tangent/axis/normal frame
//// associated with the curve at t=0:
//frames.add(getFrenetFrame(0))
//
//// start constructing RM frames:
//for t0 = 0, t0 < 1.0, t0 += step:
//// start with the previous, known frame
//x0 = frames.last
//
//// get the next frame: we're going to keep its position and tangent,
//// but we're going to recompute the axis and normal.
//t1 = t0 + step
//x1 = { o: getPoint(t1), t: getDerivative(t) }
//
//// First we reflect x0's tangent and axis of rotation onto x1,
//// through/ the plane of reflection at the point between x0 x1
//v1 = x1.o - x0.o
//c1 = v1 · v1
//        riL = x0.r - v1 * 2/c1 * v1 · x0.r
//        tiL = x0.t - v1 * 2/c1 * v1 · x0.t
//
//// note that v1 is a vector, but 2/c1 and (v1 · ...) are just
//// plain numbers, so we're just scaling v1 by some constant.
//
//// Then we reflect a second time, over a plane at x1, so that
//// the frame tangent is aligned with the curve tangent again:
//        v2 = x1.t - tiL
//c2 = v2 · v2
//
//// and we're done here:
//        x1.r = riL - v2 * 2/c2 * v2 · riL
//        x1.n = x1.r × x1.t
//        frames.add(x1)
