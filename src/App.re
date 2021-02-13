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

  React.useEffect(() =>
    switch (delta) {
    | d when d != 0. =>
      let requestId =
        AnimationFrame.requestAnimationFrame(() => setValue(v => v +. d));
      Some(() => AnimationFrame.cancelAnimationFrame(requestId));
    | _ => None
    }
  );

  value;
};

[@react.component]
let make = (~velocity=4.) => {
  <Dragon
    x={useMovementKeys("ArrowRight", "ArrowLeft", velocity)}
    y={useMovementKeys("ArrowDown", "ArrowUp", velocity)}
    width=200.
  />;
};
