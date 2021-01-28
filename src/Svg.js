const React = require('react');
const ReactDOM = require('react-dom');

exports.default = function SvgComponent({ src, children }) {
  const [svg, setSvg] = React.useState(null);
  React.useEffect(() => {
    fetch(src)
      .then((response) => response.text())
      .then(setSvg);
  }, [src]);
  const [container, setContainer] = React.useState(null);

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

  const ref = React.useCallback(
    (ref) => {
      if (ref) {
        setContainer(ref);
      }
    },
    [setContainer]
  );

  return React.createElement(
    React.Fragment,
    null,
    React.createElement(
      'div',
      React.useMemo(
        () => ({
          ref,
          dangerouslySetInnerHTML: { __html: svg },
        }),
        [ref, svg]
      ),
      null
    ),
    container instanceof SVGElement &&
      ReactDOM.createPortal(children, container)
  );
};
