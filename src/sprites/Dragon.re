type direction =
  | Left
  | Right;

module WalkAnimation = {
  [@react.component]
  let make = () => {
    <animateTransform
      attributeName="transform"
      type_="rotate"
      from="0 100 100"
      to_="-30 100 100"
      dur="0.5s"
      href="#right-arm"
      repeatCount="indefinite"
    />;
  };
};

module RotateLeftAnimation = {
  [@react.component]
  let make = () => {
    <animateTransform
      attributeName="transform"
      type_="scale"
      from="-1 1"
      to_="-1 1"
      dur="0.5s"
      href="#dragon-root"
      repeatCount="indefinite"
    />;
  };
};

[@react.component]
let make = (~x, ~y, ~width) => {
  let xRef = React.useRef(x);
  let yRef = React.useRef(y);
  let (isWalking, setIsWalking) = React.useState(() => false);
  let (direction, setDirection) = React.useState(() => Right);

  let dx = x -. xRef.current;

  React.useEffect1(
    () => {
      setDirection(direction => {
        switch (dx) {
        | v when v > 0. => Right
        | v when v < 0. => Left
        | v when v == 0. => direction
        }
      });
      None;
    },
    [|dx|],
  );

  React.useEffect1(
    () => {
      setIsWalking(_ => true);
      let timeoutId =
        Js.Global.setTimeout(() => setIsWalking(_ => false), 100);
      Some(
        () => {
          Js.Global.clearTimeout(timeoutId);
          xRef.current = x;
        },
      );
    },
    [|dx|],
  );

  <Sprite src="../assets/dragon.svg" x y width>
    {isWalking ? <WalkAnimation /> : ReasonReact.null}
    {direction == Left ? <RotateLeftAnimation /> : ReasonReact.null}
  </Sprite>;
};
