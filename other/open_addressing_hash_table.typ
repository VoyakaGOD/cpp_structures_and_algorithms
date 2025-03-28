#let red = rgb(255, 99, 71)
#let green = rgb("#4CAF50")

#let hash_table(
  cells,
  selected: (),
  crux: (),
  crux_color: green,
  columns_count: 10
) = align(center)[
  #table(
    columns: (32pt,)*columns_count,
    rows: (auto, 32pt),
    stroke: (x, y) => (y: if y > 0 {1pt}, x: if y > 0 {1pt}),
    fill: (x, y) => if (y > 0) {
      if x in crux {crux_color} 
      else if x in selected {gray}
    },
    align: horizon,
    ..(range(columns_count).map(i => [#i])),
    ..cells
  )
]

= open addressing hash table:
 - Hash(x) = $7x^2$ mod $10$
#hash_table(())

= Add 313:
- Hash(313) = 3
#hash_table(
  ([], [], [], [313], [], [], [], [], [], []),
  crux: (3,)
)

= Add 491:
- Hash(491) = 7
#hash_table(
  ([], [], [], [313], [], [], [], [491], [], []),
  crux: (7,),
)

= Add 546:
- Hash(546) = 2
#hash_table(
  ([], [], [546], [313], [], [], [], [491], [], []),
  crux: (2,)
)

= Add 552:
- Hash(552) = 8
#hash_table(
  ([], [], [546], [313], [], [], [], [491], [552], []),
  crux: (8,)
)

= Add 785:
- Hash(785) = 5
#hash_table(
  ([], [], [546], [313], [], [785], [], [491], [552], []),
  crux: (5,)
)

#pagebreak()

= Add 205:
- Hash(205) = 5
#hash_table(
  ([], [], [546], [313], [], [785], [205], [491], [552], []),
  crux: (6,),
  selected: (5,)
)

= Add 710:
- Hash(710) = 0
#hash_table(
  ([710], [], [546], [313], [], [785], [205], [491], [552], []),
  crux: (0,)
)

= Add 768:
- Hash(768) = 8
#hash_table(
  ([710], [], [546], [313], [], [785], [205], [491], [552], [768]),
  crux: (9,),
  selected: (8,)
)

= Add 860:
- Hash(860) = 0
#hash_table(
  ([710], [860], [546], [313], [], [785], [205], [491], [552], [768]),
  crux: (1,),
  selected: (0,)
)

= Add 901:
- Hash(901) = 7
#hash_table(
  ([710], [860], [546], [313], [901], [785], [205], [491], [552], [768]),
  crux: (4,),
  selected: (7,8,9,0,1,2,3)
)

= Find 313:
- Hash(313) = 3
#hash_table(
  ([710], [860], [546], [313], [901], [785], [205], [491], [552], [768]),
  crux: (3, ),
  crux_color: blue,
)

#pagebreak()

= Delete 491:
- Hash(491) = 7
#hash_table(
  ([710], [860], [546], [313], [901], [785], [205], [], [552], [768]),
  crux: (7, ),
  crux_color: red,
)

= Find 768:
- Hash(768) = 8
#hash_table(
  ([710], [860], [546], [313], [901], [785], [205], [], [552], [768]),
  crux: (9, ),
  crux_color: blue,
  selected: (8,)
)

= Delete 901:
- Hash(901) = 7
#hash_table(
  ([710], [860], [546], [313], [], [785], [205], [], [552], [768]),
  crux: (4, ),
  crux_color: red,
  selected: (7,8,9,0,1,2,3)
)

= Find 1:
- Hash(1) = 7
#hash_table(
  ([710], [860], [546], [313], [], [785], [205], [], [552], [768]),
  selected: (0,1,2,3,4,5,6,7,8,9)
)
- key not found
