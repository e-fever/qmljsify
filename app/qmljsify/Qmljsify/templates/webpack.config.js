var webpack = require("webpack");
var argv = require("minimist")(process.argv.slice(2));

var config = {
  entry: [
    "./index.js"
  ],
  devtool: false,
  resolve: {
    extensions: [".js", ".jsx"]
  },
  output: {
    path: __dirname + "/dist",
    publicPath: "/",
    filename: "bundle.js",
    library: "QML",
    libraryTarget: 'umd',
    umdNamedDefine: true
  },
  devServer: {
    contentBase: __dirname + "/build",
    hot: true
  },
  node: {
    dns: "mock",
    net: "mock"
  },
  module: {
    rules: [
      {
         use: {
            loader:'babel-loader'
         },
         test: /\.js$/
      }
    ]
  },
  plugins: []
}

module.exports = function(env) {

   const minify = env === "minify";

   if (minify) {
       config.plugins.push(
           new webpack.optimize.UglifyJsPlugin({
              compress: {
                warnings: false
              }
           })
       );
   }

   return config;
}
