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

[@react.component]
let make = (~x, ~y, ~width) => {
  let (svg, setSvg) = React.useState(_ => Js.Nullable.null);
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
          100,
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

  <>
    <Dragon
      className=[%css
        {|
        position: relative;
        width: $width++px;
        height: auto;
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
       ReactDOM.createPortal(
         <>
           {switch (action) {
            | Walk(dir) =>
              <>
                <animateTransform
                  attributeName="transform"
                  type_="rotate"
                  values="-15 100 100; 15 100 100; -15 100 100"
                  dur="0.5s"
                  href="#right-arm"
                  repeatCount="indefinite"
                />
                <animateTransform
                  attributeName="transform"
                  type_="rotate"
                  values="15 120 100; -15 120 100; 15 120 100"
                  dur="0.5s"
                  href="#left-arm"
                  repeatCount="indefinite"
                />
                {dir === Left
                   ? <animateTransform
                       attributeName="transform"
                       type_="scale"
                       from="-1 1"
                       to_="-1 1"
                       dur="0.5s"
                       href="#dragon-root"
                       repeatCount="indefinite"
                     />
                   : ReasonReact.null}
              </>
            | _ => ReasonReact.null
            }}
         </>,
         container,
       )
     | None => ReasonReact.null
     }}
  </>;
};
