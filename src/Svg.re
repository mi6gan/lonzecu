[@bs.module "./Svg.js"] [@react.component]
external make:
  (~src: string, ~className: string=?, ~children: React.element=?) =>
  React.element =
  "default";
