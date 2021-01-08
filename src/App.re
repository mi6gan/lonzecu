[@react.component]
let make = (~name) =>
  <div>
    <button> {ReasonReact.string("Hello " ++ name ++ "!")} </button>
  </div>;
