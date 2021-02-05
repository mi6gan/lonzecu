type direction =
  | Left
  | Right;
type action =
  | Walk(direction)
  | Stand(direction);

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
  let make = (~href: string, ~values: string) => {
    <animateTransform
      attributeName="transform"
      type_="rotate"
      dur="0.5s"
      repeatCount="indefinite"
      href
      values
    />;
  };
};

[@react.component]
let make = (~x, ~y, ~width) => {
  let (svg, setSvg) = React.useState(() => Js.Nullable.null);
  let (action, setAction) = React.useState(() => Stand(Right));
  let xRef = React.useRef(x);
  let dx = x -. xRef.current;

  React.useEffect1(
    () => {
      setAction(action => {
        switch (dx) {
        | v when v > 0. => Walk(Right)
        | v when v < 0. => Walk(Left)
        | _ => action
        }
      });
      let timeoutId =
        Js.Global.setTimeout(
          () =>
            setAction(_ =>
              switch (action) {
              | Walk(dir) => Stand(dir)
              | _ => action
              }
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
    action == Stand(Left) || action == Walk(Left) ? "scaleX(-1)" : "";

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
        ~width=string_of_int(int_of_float(width)) ++ "px",
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
       ReactDOM.createPortal(
           {switch (action) {
            | Walk(_) =>
              <>
                <RotateAnimation
                  href="#right-arm"
                  values="-15 100 100; 15 100 100; -15 100 100"
                />
                <RotateAnimation
                  href="#right-leg"
                  values="10 88 172; -10 88 172; 10 88 172"
                />
                <RotateAnimation
                  href="#left-arm"
                  values="15 120 100; -15 120 100; 15 120 100"
                />
                <RotateAnimation
                  href="#left-leg"
                  values="-10 118 151; 10 108 151; -10 118 151"
                />
              </>
            | _ => ReasonReact.null
            }}
         ,
         container,
       )
     | None => ReasonReact.null
     }}
  </>;
};
