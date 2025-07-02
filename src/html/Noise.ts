import CRunWasmExtWrapper from "../../sdk/lib/Html/CRunWasmExtWrapper";
import { extInstance, cppLand } from "../../sdk/lib/Html/CRunWasmExtWrapper";
import "../../sdk/lib/Html/Runtime.d.ts"



// esbuild bundles everything in a way that nothing gets exposed to outside and nothing can conflict
// Only extension class is global
// Override any defaults in CRunWasmExtWrapper here
export default class CRunNoise extends CRunWasmExtWrapper {
    action(num: number, act: CActExtension) {
        switch (num) {
        case 26:    // fill_surface_obj_with_noise
            // TODO: handle this
            console.log(act.getParamObject(this.rh!, 0).ext);
            break;

        default:
            super.action(num, act);;
        }
    }
}