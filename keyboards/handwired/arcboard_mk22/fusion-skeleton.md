# Managing Shared Curves Across Interdependent Fusion Parts

## Brief Summary (Tactical)

- Don't derive parts from each other — create one independent **skeleton file** containing only shared curves, planes, axes, and points.
- Every dependent part (shell, middle, fascia) uses **Insert Derive** to pull from the skeleton directly — a star pattern, not a chain.
- Never derive anything *back* into the skeleton from a downstream part — that's what causes circular dependency errors.
- Place the **Insert Derive feature at the start of the timeline** in each dependent part, so all later features can reference it.
- Keep the skeleton content consolidated in **one Insert Derive feature per part** — edit it to add/remove content rather than creating multiple derive features.
- When editing a Derive feature to add components, **add one at a time** — doing multiple at once has been reported to disrupt existing component-level derives.
- The skeleton isn't just sketches — **shared planes, axes, and reference points** belong there too, whenever more than one part must agree on them.
- For your existing middle/fascia parts: the risky step is **redirecting their existing sketches/features to reference the new skeleton geometry** — plan that migration deliberately, not incrementally.
- Solid operations like loft-cut aren't the anti-pattern — **tracing or copying geometry instead of deriving it** is.
- Watch for **reference failures / cached geometry** warnings — Fusion can silently fall back to stale geometry if a derived reference breaks; don't ignore that warning.

---

## 1. The Core Problem

You're designing a top-shell and bottom-shell (surface lofts with intersection curves) alongside a middle component and fascia that must mate precisely with them. The middle component and fascia already exist; the shells don't yet. Both sides need to reference the same critical curves, but Fusion blocks direct circular references between designs.

## 2. Why Direct Derive Fails Here

Fusion detects and blocks **circular references** — if design A links into B, and B links (even indirectly) back into A, the operation is refused. This is exactly what happens if the shell derives from the middle/fascia while the middle/fascia also derive from the shell. There is no workaround within that direct topology; the fix is architectural.

## 3. The Skeleton / Master-Geometry Pattern (General CAD Methodology)

This is a general, cross-CAD practice — not a named Fusion-specific feature — but it maps cleanly onto Fusion's Derive/Insert Derive tools.

**Core principles:**

1. **Separate control geometry from shape geometry.** The skeleton contains only what defines relationships between parts: intersection curves, mating edges, key planes/axes, critical points. No solid features, no cosmetic surfacing.
2. **Author the skeleton independently.** It's driven by top-level product requirements, not by any single part's internal solution. If you're tempted to derive a curve from the shell back into the skeleton, that curve belongs in the skeleton from the start.
3. **Star topology, not a chain.** Shell, middle component, and fascia each derive directly from the skeleton. None derive from each other.
4. **Treat skeleton edits as high-consequence.** Everything depends on it — change it deliberately.
5. **Downstream parts consume skeleton geometry for both surfacing and solid ops.** Loft rails, intersection curves, loft-cuts — all fine, as long as their input geometry traces back to the skeleton via a live derive link, not a copy or trace.

**Does the skeleton include planes and axes, or just sketches?**
Commonly more than sketches:
- **Construction planes** — shared parting lines, symmetry planes, datum references.
- **Construction axes** — shared rotational/revolve axes or pattern references.
- **Sketches / 3D sketch curves** — intersection curves, mating profiles, rail curves (usually the bulk of the content).
- **Reference points** — shared fastener centers, alignment features.

The test: if more than one part must agree on a piece of geometry, and divergence would break the assembly, it belongs in the skeleton — regardless of whether it's a curve, plane, axis, or point.

## 4. Your Specific Constraint: Retrofitting Existing Parts

The textbook skeleton pattern assumes the skeleton exists first for everyone. Your case is different — the middle component and fascia already exist independently. Practical implications:

- Scope the skeleton to **exactly** what's needed to mediate between old and new parts — don't try to retroactively skeletonize the entire product.
- The middle/fascia parts need a **migration step**: redirecting their existing sketches/mating features to reference the new skeleton geometry, replacing whatever they used to mate against before the shell existed. This redirection is where most of the fragility risk actually lives.

## 5. Insert Derive: Implementation Details

**Documented mechanics** (from Fusion help):
- **Derive** pushes geometry from the active design into a new or existing design.
- **Insert Derive** pulls geometry from another design into the active design.
- Both create a link — updates to the source propagate to the destination automatically.
- Derivable content includes: components, bodies, sketches, construction geometry, sheet metal flat patterns, favorite parameters, and feature parameters.
- The link can later be edited (`Edit Derive Feature`) or permanently broken (`Break Link`, which converts derived objects to base features).

**Timeline placement:**
Put Insert Derive **at or near the beginning of the timeline** in each dependent part. Anything downstream (sketches, lofts, loft-cuts, edging) that needs the shared geometry must have that geometry already present — placing the derive feature later breaks this and risks fragile timeline reordering.

**Consolidation:**
Keep it as **one Insert Derive feature per part**, edited over time to include more or less content, rather than scattering multiple separate derive features through the timeline. This gives you one edit point and avoids a later derive feature accidentally landing after a feature that needed its content.

**Known risk:** editing a Derive feature to add multiple components at once has been reported to disrupt other existing component-level derives in the design. The documented workaround is to **add one component at a time**.

## 6. Is Solid Loft-Cut an Anti-Pattern Here?

No — the operation itself isn't the problem. Loft-cut consuming sketch/curve geometry that arrived via a live Insert Derive link is a normal, supported use. The actual anti-pattern is **how the input geometry got there**:
- Loft-cut fed by Insert Derive'd sketches/curves — fine.
- Loft-cut fed by geometry copied or manually traced from an exported STEP — fragile, loses associativity, breaks the moment the source curve changes.

## 7. Failure Modes to Watch For

- **Reference failures / cached geometry:** if a derived reference breaks, Fusion can silently fall back to cached geometry and show a warning rather than failing outright. Don't ignore this warning — it means a feature is no longer actually tracking its live source.
- **Same-sketch projection constraint:** 3D-projected geometry can't live in the same sketch as its source — needs a separate sketch, which affects how you structure the skeleton's intersection-curve sketches.
- **Circular reference detection:** if Undo/Redo would recreate a circular reference, Fusion blocks it too — you may need to save/close/reopen to clear undo history in edge cases.

---

## Sources

- Tutorial: Top-down design method of assembly — https://help.autodesk.com/view/NINVFUS/ENU/?guid=GUID-929B8937-A1AA-4B97-AEB9-3E1E9FBCFDAE
- Tutorial conclusion: Top-down design — https://help.autodesk.com/view/NINVFUS/ENU/?guid=GUID-AE50B974-1496-4397-A9B5-8FF5460210FF
- Derived design features — https://help.autodesk.com/view/NINVFUS/ENU/?guid=ASM-DERIVED-DESIGN-FEATURES
- Derive design features from one design into another — https://help.autodesk.com/view/NINVFUS/ENU/?guid=ASM-DERIVE
- Circular References — https://help.autodesk.com/view/NINVFUS/ENU/?guid=ASM-REF-CIRCULAR-REFERENCES
- Loft a surface body — https://help.autodesk.com/view/NINVFUS/ENU/?guid=SFC-LOFT
- Loft reference (Surface) — https://help.autodesk.com/view/NINVFUS/ENU/?guid=SFC-REF-LOFT-DLG
- Reference failures... cached geometry — https://www.autodesk.com/support/technical/article/caas/sfdcarticles/sfdcarticles/Reference-failures-The-model-is-using-cached-geometry-to-solve-in-ribs-in-Autodesk-Fusion.html
- "Projecting sketch geometry onto the same sketch is not supported" — https://www.autodesk.com/support/technical/article/caas/sfdcarticles/sfdcarticles/Not-support-projecting-sketch-geometry-into-same-sketch-or-geometry-Unable-to-Project-Sketch-to-Surface-in-Fusion-360.html
- "Editing a derive feature removes existing component level derives" — https://www.autodesk.com/support/technical/article/caas/sfdcarticles/sfdcarticles/Editing-a-derive-feature-removes-existing-component-level-derives-in-Fusion.html
