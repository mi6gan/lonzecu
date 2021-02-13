type direction =
  | Left
  | Right;
type action =
  | Walk
  | Stop
  | Stand;
type state =
  | State(action, direction);

module Dragon = {
  [@bs.module "./Dragon.svg"] [@react.component]
  external make:
    (
      ~className: string=?,
      ~style: ReactDOM.style=?,
      ~children: React.element=?,
      ~ref: ReactDOM.domRef
    ) =>
    React.element =
    "default";
};

module RotateAnimation = {
  [@react.component]
  let make = (~href, ~values, ~dur=?, ~repeatCount=?, ~onEndEvent) => {
    let (element, setElement) = React.useState(_ => Js.Nullable.null);

    React.useEffect2(
      () =>
        switch (Js.toOption(element)) {
        | Some(domElement) =>
          let node = ReactDOM.domElementToObj(domElement);
          switch (repeatCount) {
          | None =>
            node##endElement();
            None;
          | Some("indefinite") =>
            node##beginElement();
            None;
          | Some(_) =>
            node##addEventListener("endEvent", onEndEvent);
            Some(() => node##removeEventListener("endEvent", onEndEvent));
          };
        | None => None
        },
      (repeatCount, element),
    );
    <animateTransform
      ref={ReactDOM.Ref.callbackDomRef(element => {
        setElement(null =>
          switch (Js.toOption(element)) {
          | None => null
          | Some(_) => element
          }
        )
      })}
      fill="freeze"
      attributeName="transform"
      type_="rotate"
      ?dur
      ?repeatCount
      href
      values
    />;
  };
};

module Utils = {
  let toOption =
    fun
    | "" => None
    | v => Some(v);

  let toOptions =
    fun
    | (a, b) => (toOption(a), toOption(b));
};

[@react.component]
let make = (~x, ~y, ~width) => {
  let (svg, setSvg) = React.useState(() => Js.Nullable.null);
  let (action, setAction) = React.useState(() => State(Stand, Right));
  let xRef = React.useRef(x);
  let dx = x -. xRef.current;

  React.useEffect1(
    () => {
      setAction(action => {
        switch (dx) {
        | v when v != 0. => State(Walk, v > 0. ? Right : Left)
        | _ => action
        }
      });
      let timeoutId =
        Js.Global.setTimeout(
          () =>
            setAction(
              fun
              | State(Walk, dir) => State(Stop, dir)
              | v => v,
            ),
          250,
        );
      Some(
        () => {
          Js.Global.clearTimeout(timeoutId);
          xRef.current = x;
        },
      );
    },
    [|dx|],
  );

  let scale =
    switch (action) {
    | State(_, Left) => "scaleX(-1)"
    | _ => ""
    };

  let onEndEvent =
    React.useCallback1(
      _ =>
        setAction(
          fun
          | State(_, dir) => State(Stand, dir),
        ),
      [|setAction|],
    );

  <>
    <Dragon
      className=[%css
        {|
        position: relative;
        width: $width++px;
        height: auto;
        transform: $scale;
        |}
      ]
      style={ReactDOM.Style.make(
        ~left=string_of_int(int_of_float(x)) ++ "px",
        ~top=string_of_int(int_of_float(y)) ++ "px",
        (),
      )}
      ref={ReactDOM.Ref.callbackDomRef(element =>
        setSvg(svg =>
          switch (Js.toOption(element)) {
          | None => svg
          | Some(_) => element
          }
        )
      )}
    />
    {switch (Js.toOption(svg)) {
     | Some(container) =>
       let (dur, repeatCount) =
         Utils.toOptions(
           switch (action) {
           | State(Walk, _) => ("0.5s", "indefinite")
           | State(Stop, _) => ("0.5s", "1")
           | State(_, _) => ("", "")
           },
         );

       ReactDOM.createPortal(
         <>
           <RotateAnimation
             href="#right-arm"
             values="0; 15; 0; -15; 0"
             ?repeatCount
             ?dur
             onEndEvent
           />
           <RotateAnimation
             href="#right-leg"
             values="0; 10; 0; -10; 0"
             ?repeatCount
             ?dur
             onEndEvent
           />
           <RotateAnimation
             href="#left-arm"
             values="0; -15; 0; 15; 0"
             ?repeatCount
             ?dur
             onEndEvent
           />
           <RotateAnimation
             href="#left-leg"
             values="0; -10; 0; 10; 0"
             ?repeatCount
             ?dur
             onEndEvent
           />
         </>,
         container,
       );
     | None => ReasonReact.null
     }}
  </>;
};
