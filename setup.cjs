module.exports = {
  name: 'setup',
  factory: () => ({
    hooks: {
      setupScriptEnvironment(_, env) {
        if (/^test.*$/.test(env['npm_lifecycle_event'])) {
          env.NODE_ENV = 'test';
        } else if (!env.NODE_ENV) {
          env.NODE_ENV = 'development';
        }
      },
    },
  }),
};
