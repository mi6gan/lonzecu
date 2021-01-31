module Provider = {
  let context = React.createContext([]);
  include React.Context;
  [@bs.obj]
  external makeProps:
    (~children: React.element, ~value: list(string), unit) => _;
  let make = React.Context.provider(context);
};

[@react.component]
let make = (~children) => {
  let (value, setValue) = React.useState(() => []);
  <div
    className=[%css {|
      outline-style: none;
    |}]
    onKeyDown={React.useCallback(event => {
      let key = ReactEvent.Keyboard.key(event);
      setValue(value =>
        List.exists(k => k == key, value) ? value : [key, ...value]
      );
    })}
    onKeyUp={React.useCallback(event => {
      let key = ReactEvent.Keyboard.key(event);
      setValue(value => List.filter(k => k !== key, value));
    })}
    ref={ReactDOM.Ref.callbackDomRef(container => {
      switch (Js.toOption(container)) {
      | Some(element) => ReactDOM.domElementToObj(element)##focus()
      | None => ()
      }
    })}
    tabIndex=0>
    <Provider value> children </Provider>
  </div>;
};
