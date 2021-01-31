module.exports = {
  presets: [
    '@babel/env',
    '@babel/react',
    ['@dr.pogodin/babel-preset-svgr', { svgr: { ref: true } }],
  ],
  plugins: [
    '@babel/plugin-proposal-class-properties',
    '@babel/plugin-proposal-numeric-separator',
    'macros',
  ],
};
