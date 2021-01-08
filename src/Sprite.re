[@react.component]
let make = (~x: float, ~y: float, ~width: float, ~src) => {
  let left = int_of_float(x);
  let top = int_of_float(y);
  <img
    className=[%css
      {|
      position: relative;
      width: $width++px;
      left: $left++px;
      top: $top++px;
    |}
    ]
    src
  />;
};
