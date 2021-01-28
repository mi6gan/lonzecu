const React = require('react');
const ReactDOM = require('react-dom');

exports.default = function SvgComponent({ src, children, ...props }) {
  const [svg, setSvg] = React.useState(null);
  React.useEffect(() => {
    fetch(src)
      .then((response) => response.text())
      .then(setSvg);
  });
  const [container, setContainer] = React.useState(null);
  console.log(container);

  React.useEffect(() => {
    if (svg && !(container instanceof SVGElement)) {
      const intervalId = setInterval(() => {
        const svgElement = container && container.querySelector('svg');
        if (svgElement) {
          clearInterval(intervalId);
          setContainer(svgElement);
        }
      }, 250);
      return () => {
        clearInterval(intervalId);
      };
    }
  }, [container, svg]);

  return React.createElement(React.Fragment, null, [
    React.createElement('div', {
      ...props,
      ref: React.useCallback((ref) => {
        if (ref) {
          setContainer(ref);
        }
      }, [setContainer]),
      dangerouslySetInnerHTML: { __html: svg },
    }),
    container instanceof SVGElement &&
      ReactDOM.createPortal(children, container),
  ]);
};
