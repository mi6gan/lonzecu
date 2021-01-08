module AnimationFrame = {
  type requestID;

  [@bs.val]
  external requestAnimationFrame: (unit => unit) => requestID =
    "requestAnimationFrame";
  [@bs.val]
  external cancelAnimationFrame: requestID => unit = "cancelAnimationFrame";
};

let useMovementKeys = (incKey: string, decKey: string, velocity: float) => {
  let (value, setValue) = React.useState(() => 0.);
  let keyboard = React.useContext(Keyboard.Provider.context);
  let delta =
    switch (keyboard) {
    | k when List.exists(v => v == incKey, k) => velocity
    | k when List.exists(v => v == decKey, k) => -. velocity
    | _ => 0.
    };
  React.useEffect(() => {
    if (delta != 0.) {
      let _ =
        AnimationFrame.requestAnimationFrame(() =>
          setValue(_ => value +. delta)
        );
      ();
    };
    None;
  });
  value;
};

[@react.component]
let make = (~velocity=5.) => {
  <div
    className=[%css {|
      position: relative;
      width: 200px;
    |}]>
    <Sprite
      x={useMovementKeys("ArrowRight", "ArrowLeft", velocity)}
      y={useMovementKeys("ArrowDown", "ArrowUp", velocity)}
      src="../assets/dragon.svg"
    />
  </div>;
};
