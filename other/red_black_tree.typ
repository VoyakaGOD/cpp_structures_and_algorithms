#import "@preview/cetz:0.3.4"
#import cetz.draw: *

#let r = rgb("C44444")
#let b = luma(55%)

#let rbtree(data, route: ()) = align(
  center,
  cetz.canvas({
    cetz.tree.tree(
      data,
      direction: "down",
      spread: 1.5, 
      grow: 1.5,
      draw-node: (node, ..) => {
        if type(node.content) == dictionary {
          circle(
            (), 
            radius: .45, 
            fill: node.content.color, 
            stroke: if node.content.text in route {blue + 2pt} else {black}
          )
          content((), text(black, [#node.content.text]))
        }
        else {
          content((), [])
        }
      },
      draw-edge: (from, to, src, dst, ..) => {
        if type(dst.content) == dictionary {
          let (a, b) = (from + ".center", to + ".center")
          line(
            (a, 0, b), 
            (b, 0, a), 
            stroke: if dst.content.text in route {blue + 2pt} else {black}
          )
        }
      }
    )
  })
)

#let node(
  color,
  text,
  left_child,
  right_child
) = {((color: color, text: text), left_child, right_child)}

= red-black tree:
#rbtree(node(b, "null", [], []))

= Add 824:
#rbtree(node(b, 824, [], []))

= Add 809:
- 809 < 824
#rbtree(node(b, 824, node(b, 809, [], []), []))

= Add 736:
- 736 < 809 < 824
#rbtree(node(b, 824, node(b, 809, node(b, 736, [], []), []), []))
- rotate right
#rbtree(node(b, 809, node(b, 736, [], []), node(b, 824, [], [])))

#pagebreak()

= Add 148:
- 148 < 736 < 809
#rbtree(node(b, 809, node(b, 736, node(r, 148, [], []), []), node(b, 824, [], [])))

= Add 820:
- 809 < 820 < 824
#rbtree(node(b, 809, node(b, 736, node(r, 148, [], []), []), node(b, 824, node(r, 820, [], []), [])))

= Add 681:
- 148 < 681 < 736 < 809
#rbtree(node(b, 809, node(b, 736, node(r, 148, [], node(b, 681, [], [])), []), node(b, 824, node(r, 820, [], []), [])))

#pagebreak()

- rotate left
#rbtree(node(b, 809, node(b, 736, node(b, 681, node(r, 148, [], []), []), []), node(b, 824, node(r, 820, [], []), [])))
- rotate right
#rbtree(node(b, 809, node(b, 681, node(r, 148, [], []), node(b, 736, [], [])), node(b, 824, node(r, 820, [], []), [])))
- recolor
#rbtree(node(b, 809, node(b, 681, node(r, 148, [], []), node(r, 736, [], [])), node(b, 824, node(r, 820, [], []), [])))

#pagebreak()

= Add 7:
#rbtree(node(b, 809, node(b, 681, node(r, 148, node(b, 7, [], []), []), node(r, 736, [], [])), node(b, 824, node(r, 820, [], []), [])))
- recolor
#rbtree(node(b, 809, node(r, 681, node(b, 148, node(r, 7, [], []), []), node(b, 736, [], [])), node(b, 824, node(r, 820, [], []), [])))

= Add 571:
- 148 < 571 < 681 < 809
#rbtree(node(b, 809, node(r, 681, node(b, 148, node(r, 7, [], []), node(r, 571, [], [])), node(b, 736, [], [])), node(b, 824, node(r, 820, [], []), [])))

#pagebreak()

= Add 304:
- 148 < 304 < 571 < 681 < 809
#rbtree(node(b, 809, node(r, 681, node(b, 148, node(r, 7, [], []), node(r, 571, node(b, 304, [], []), [])), node(b, 736, [], [])), node(b, 824, node(r, 820, [], []), [])))
- recolor
#rbtree(node(b, 809, node(r, 681, node(r, 148, node(b, 7, [], []), node(b, 571, node(r, 304, [], []), [])), node(b, 736, [], [])), node(b, 824, node(r, 820, [], []), [])))

#pagebreak()

- rebalance [148] > rotate right
#rbtree(node(r, 681, node(r, 148, node(b, 7, [], []), node(b, 571, node(r, 304, [], []), [])), node(b, 809, node(b, 736, [], []), node(b, 824, node(r, 820, [], []), []))))
- rebalance [148] > recolor
#rbtree(node(b, 681, node(r, 148, node(b, 7, [], []), node(b, 571, node(r, 304, [], []), [])), node(r, 809, node(b, 736, [], []), node(b, 824, node(r, 820, [], []), []))))

#pagebreak()

= Add 415:
- 148 < 304 < 415 < 571 < 681
#rbtree(node(b, 681, node(r, 148, node(b, 7, [], []), node(b, 571, node(r, 304, [], node(b, 415, [], [])), [])), node(r, 809, node(b, 736, [], []), node(b, 824, node(r, 820, [], []), []))))
-rotate left
#rbtree(node(b, 681, node(r, 148, node(b, 7, [], []), node(b, 571, node(b, 415, node(r, 304, [], []), []), [])), node(r, 809, node(b, 736, [], []), node(b, 824, node(r, 820, [], []), []))))

#pagebreak()

-rotate right
#rbtree(node(b, 681, node(r, 148, node(b, 7, [], []), node(b, 415, node(r, 304, [], []), node(b, 571, [], []))), node(r, 809, node(b, 736, [], []), node(b, 824, node(r, 820, [], []), []))))
- recolor
#rbtree(node(b, 681, node(r, 148, node(b, 7, [], []), node(b, 415, node(r, 304, [], []), node(r, 571, [], []))), node(r, 809, node(b, 736, [], []), node(b, 824, node(r, 820, [], []), []))))

= Find 148:
- 148 < 681
#rbtree(node(b, 681, node(r, 148, node(b, 7, [], []), node(b, 415, node(r, 304, [], []), node(r, 571, [], []))), node(r, 809, node(b, 736, [], []), node(b, 824, node(r, 820, [], []), []))), route: (681, 148))

#pagebreak()

= Get max:
- MAX is the most right item
- MAX = 824
#rbtree(node(b, 681, node(r, 148, node(b, 7, [], []), node(b, 415, node(r, 304, [], []), node(r, 571, [], []))), node(r, 809, node(b, 736, [], []), node(b, 824, node(r, 820, [], []), []))), route: (681, 809, 824))

= Find 568:
- 148 < 304 < 415 < 568 < 571 < 681
#rbtree(node(b, 681, node(r, 148, node(b, 7, [], []), node(b, 415, node(r, 304, [], []), node(r, 571, [], []))), node(r, 809, node(b, 736, [], []), node(b, 824, node(r, 820, [], []), []))), route: (681, 148, 415, 571))
- key not found

#pagebreak()

= Delete 148:
Next key value is 304
#rbtree(node(b, 681, node(r, 304, node(b, 7, [], []), node(b, 415, [], node(r, 571, [], []))), node(r, 809, node(b, 736, [], []), node(b, 824, node(r, 820, [], []), []))))

= Get min:
- MIN is the most left item
- MIN = 7
#rbtree(node(b, 681, node(r, 304, node(b, 7, [], []), node(b, 415, [], node(r, 571, [], []))), node(r, 809, node(b, 736, [], []), node(b, 824, node(r, 820, [], []), []))), route: (681, 304, 7))

#pagebreak()

= Find 571:
- 304 < 415 < 571 < 681
#rbtree(node(b, 681, node(r, 304, node(b, 7, [], []), node(b, 415, [], node(r, 571, [], []))), node(r, 809, node(b, 736, [], []), node(b, 824, node(r, 820, [], []), []))), route: (681, 304, 415, 571))

= Delete 571:
[571] is leaf
#rbtree(node(b, 681, node(r, 304, node(b, 7, [], []), node(b, 415, [], [])), node(r, 809, node(b, 736, [], []), node(b, 824, node(r, 820, [], []), []))))
