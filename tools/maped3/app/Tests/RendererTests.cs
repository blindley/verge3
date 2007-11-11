using System;
using System.Collections.Generic;
using System.Text;

using NUnit.Framework;
using winmaped2;

namespace winmaped2.Tests {
    [TestFixture]
    public class RendererTests : RenderFixture {
        [Test]
        public void TestDrawImage() {
            int[] pixels = new int[16 * 16];
            for (int i = 0; i < pixels.Length; i++) {
                pixels[i] = 1;
            }
            Image img = new Image(16, 16, pixels);

            pr2.Render.Image destImage = pr2.Render.Image.create(16, 16);
            Renderer ren = new Renderer(destImage);

            ren.renderTile32(img, 0, 0, true);

            int[] resultPixels = ren.BackBuffer.getArray();
            Assert.AreEqual(pixels, resultPixels);
        }

        [Test]
        public void RenderSizeIsImageSize() {
            const int width = 42;
            const int height = 99;
            pr2.Render.Image backBuffer = pr2.Render.Image.create(width, height);
            Renderer ren = new Renderer(backBuffer);
            Assert.AreEqual(ren.Width, backBuffer.width);
            Assert.AreEqual(ren.Height, backBuffer.height);
        }

        [Test]
        public void RenderDrawsDeathMagenta() {
            Image src = new Image(16, 16, CreatePixels(16, 16, MAGENTA));
            pr2.Render.Image dest = pr2.Render.Image.create(16, 16);

            Renderer ren = new Renderer(dest);
            ren.render(src, 0, 0, true);
            Assert.AreEqual(dest.getArray(), src.Pixels);
        }

        [Test]
        public void RenderSkipsDeathMagenta() {
            Image src = new Image(16, 16, CreatePixels(16, 16, MAGENTA));
            pr2.Render.Image dest = pr2.Render.Image.create(16, 16);
            dest.clear(BLACK);

            Renderer ren = new Renderer(dest);
            ren.render(src, 0, 0, false);
            Assert.AreEqual(dest.getArray(), CreatePixels(16, 16, BLACK));
        }
    }
}
