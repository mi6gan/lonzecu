[@react.component]
let make = () => {
  let (x, setX) = React.useState(_ => 0);
  let (y, setY) = React.useState(_ => 0);
  <div
    ref={ReactDOM.Ref.callbackDomRef(container => {
      switch (Js.toOption(container)) {
      | Some(element) => ReactDOM.domElementToObj(element)##focus()
      | None => ()
      }
    })}
    onKeyDown={React.useCallback(event => {
      Js.log(ReactEvent.Keyboard.key(event));
      switch (ReactEvent.Keyboard.key(event)) {
      | "ArrowUp" => setY(y => y - 1)
      | "ArrowDown" => setY(y => y + 1)
      | "ArrowLeft" => setX(x => x - 1)
      | "ArrowRight" => setX(x => x + 1)
      | _ => ()
      };
    })}
    tabIndex=0
    style={ReactDOM.Style.make(~position="relative", ~width="200px", ())}>
    <Sprite x y src="../assets/dragon.svg" />
  </div>;
};
