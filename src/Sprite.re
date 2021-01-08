[@react.component]
let make = (~x: float, ~y: float, ~src) => {
  let left = int_of_float(x);
  let top = int_of_float(y);
  <img
    className=[%css
      {|
      position: absolute;
      width: 100%;
      left: $left++px;
      top: $top++px;
    |}
    ]
    src
  />;
};
