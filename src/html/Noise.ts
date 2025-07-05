import CRunWasmExtWrapper from "../../sdk/lib/Html/CRunWasmExtWrapper";
import { extInstance, cppLand } from "../../sdk/lib/Html/CRunWasmExtWrapper";
import "../../sdk/lib/Html/Runtime.d.ts"



let cppLandExtra = {
    fill_buffer_with_noise: extInstance.exports["fill_buffer_with_noise"] as (extPtr: number, buf_ptr: number, width: number, height: number, xoffset: number, yoffset: number, zoffset: number, flags: number) => void,
}

// esbuild bundles everything in a way that nothing gets exposed to outside and nothing can conflict
// Only extension class is global
// Override any defaults in CRunWasmExtWrapper here
export default class CRunNoise extends CRunWasmExtWrapper {
    action(num: number, act: CActExtension) {
        switch (num) {
        case 26:    // fill_surface_obj_with_noise
            // Params
            const ext = act.getParamObject(this.rh!, 0);
            const xOffset = act.getParamExpression(this.rh, 1) as number;
            const yOffset = act.getParamExpression(this.rh, 2) as number;
            const zOffset = act.getParamExpression(this.rh, 2) as number;
            let flags = act.getParamExpression(this.rh, 4) as number;

            // ext.hoIdentifier;
            const surface = ext.ext as any;
            console.log(surface);

            // Get surface object rendering context
            const currentImage = surface.oSurf.imageList[surface.oSurf.selectedImage] as any;
            const context = currentImage.context as CanvasRenderingContext2D;
            const w: number = currentImage.getWidth();
            const h: number = currentImage.getHeight();

            // Get current image data
            const imageData = context.getImageData(0, 0, w, h);
            console.log(imageData)

            // Copy it to cpp side
            const cppBufferPtr = cppLand.malloc(imageData.data.byteLength);
            const bufferDV = new DataView(cppLand.memory.buffer, cppBufferPtr, imageData.data.byteLength);

            for (let i = 0; i < imageData.data.byteLength; i++) {
                bufferDV.setUint8(i, imageData.data[i]);
            }

            if(currentImage.useTransparentColor) {
                currentImage.updateTransparent = true;
                flags |= 1<<6;  // FillAlpha255
            }

            cppLandExtra.fill_buffer_with_noise(this.cppExtPtr, cppBufferPtr, imageData.width, imageData.height, xOffset, yOffset, zOffset, flags);

            // Copy image data back
            for (let i = 0; i < imageData.data.byteLength; i++) {
                imageData.data[i] = bufferDV.getUint8(i);
            }

            cppLand.free(cppBufferPtr);

            context.putImageData(imageData, 0, 0);
            surface.oSurf.redraw()
            break;

        default:
            super.action(num, act);
        }
    }
}
