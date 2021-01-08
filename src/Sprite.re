type pos = {
  x: int,
  y: int,
};

[@react.component]
let make = (~x: int, ~y: int, ~src) =>
  <img
    style={ReactDOM.Style.make(
      ~position="absolute",
      ~left=Pervasives.string_of_int(x) ++ "px",
      ~top=Pervasives.string_of_int(y) ++ "px",
      ~width="100%",
      (),
    )}
    src
  />;
