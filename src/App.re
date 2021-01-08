[@react.component]
let make = () => {
  let (x: int, setX) = React.useState(_ => 0);
  let (y: int, setY) = React.useState(_ => 0);
  <div
    onKeyDown={React.useCallback(event => {
      switch (ReactEvent.Keyboard.key(event)) {
      | "ArrowUp" => setY(y => y - 1)
      | "ArrowDown" => setY(y => y + 1)
      | "ArrowLeft" => setX(x => x - 1)
      | "ArrowRight" => setX(x => x + 1)
      | _ => ()
      }
    })}
    tabIndex=0
    style={ReactDOM.Style.make(~position="relative", ~width="200px", ())}>
    <Sprite x y src="../assets/dragon.svg" />
  </div>;
};
