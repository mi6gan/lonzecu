module AnimationFrame = {
  type requestID;

  [@bs.val]
  external requestAnimationFrame: (unit => unit) => requestID =
    "requestAnimationFrame";
  [@bs.val]
  external cancelAnimationFrame: requestID => unit = "cancelAnimationFrame";
};

[@react.component]
let make = (~velocity=5.) => {
  let (x, setX) = React.useState(() => 0.);
  let (y, setY) = React.useState(() => 0.);
  let keyboard = React.useContext(Keyboard.Provider.context);
  let dy =
    switch (keyboard) {
    | k when List.exists(v => v == "ArrowDown", k) => 1.
    | k when List.exists(v => v == "ArrowUp", k) => (-1.)
    | _ => 0.
    };
  let dx =
    switch (keyboard) {
    | k when List.exists(v => v == "ArrowRight", k) => 1.
    | k when List.exists(v => v == "ArrowLeft", k) => (-1.)
    | _ => 0.
    };

  React.useEffect(() => {
    if (dy != 0.) {
      let _ =
        AnimationFrame.requestAnimationFrame(() =>
          setY(_ => y +. dy *. velocity)
        );
      ();
    };
    None;
  });

  React.useEffect(() => {
    if (dx != 0.) {
      let _ =
        AnimationFrame.requestAnimationFrame(() =>
          setX(_ => x +. dx *. velocity)
        );
      ();
    };
    None;
  });

  <div
    className=[%css {|
      position: relative;
      width: 200px;
    |}]>
    <Sprite x y src="../assets/dragon.svg" />
  </div>;
};
