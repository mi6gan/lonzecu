module StyledContainer = [%styled
  (~w, ~left, ~top) => {j|
  position: relative;
  left: $left++px;
  top: $top++px;
  width: $w++px;
  svg {
    width: 100%;
    height: auto;
  }
|j}
];

[@react.component]
let make =
    (
      ~x: float,
      ~y: float,
      ~width: float,
      ~src,
      ~children: React.element=ReasonReact.null,
    ) => {
  let left = string_of_int(int_of_float(x));
  let top = string_of_int(int_of_float(y));

  <StyledContainer w={string_of_int(int_of_float(width))} left top>
    <Svg src> children </Svg>
  </StyledContainer>;
};
