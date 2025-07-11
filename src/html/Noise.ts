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
            const zOffset = act.getParamExpression(this.rh, 3) as number;
            let flags = act.getParamExpression(this.rh, 4) as number;

            const surface_id = 0x53555246; // (('S'<<24)|('U'<<16)|('R'<<8)|('F'));
            if(ext.hoIdentifier != surface_id) {
                return;
            }

            const surface = ext.ext as any;

            // Get surface object rendering context
            let currentImage = surface.oSurf.imageList[surface.oSurf.selectedImage] as any;
            let context = currentImage.context as CanvasRenderingContext2D;

            // Get current image data
            let imageData = context.getImageData(0, 0, currentImage.getWidth(), currentImage.getHeight());

            // Copy it to cpp side
            const cppBufferPtr = cppLand.malloc(imageData.data.byteLength);
            let bufferDV = new DataView(cppLand.memory.buffer, cppBufferPtr, imageData.data.byteLength);

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
